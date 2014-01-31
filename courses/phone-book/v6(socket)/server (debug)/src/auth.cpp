#include "auth.h"
#include "fileio.h"
#include "md5.h"
#include <fstream>


const int max_length = 20;

Authorize::Authorize()
{
    _file = "data/info";
    try
    {
        readData();     
    }
    catch (const FileException & e)
    {
        std::cerr << e.what() << endl;
    }
}

Authorize::~Authorize()
{
    try
    {
        updateData();     
    }
    catch (const FileException & e)
    {
        std::cerr << e.what() << endl;
    }
}

void
Authorize::readData() 
{
    ifstream fin(_file.c_str(), ios::binary);
    if (!fin)
        throw FileException(_file, "read");
    else
    {   
        size_t count;
        char name[max_length]={0}, key[40]={0};
        fin.read((char *)&count, sizeof(count));
        for (int i=0; i < count ; ++i)
        {
            fin.read(name, max_length);
            fin.read(key, 32);
            _accounts[name] = key;
        }
        fin.close();
    }
}

void
Authorize::updateData()
{
    ofstream fout(_file.c_str(), ios::binary);
    if (fout)
    {   
        long count = _accounts.size();
        fout.write((char *)&count, sizeof(long));
        map<string, string>::iterator i = _accounts.begin();
        for ( ; i != _accounts.end() ; ++i)
        {
            fout.write(i->first.c_str(), max_length);
            fout.write(i->second.c_str(), 32);
        }
        fout.close();
    }
    else
        throw FileException(_file, "write");
}

bool
Authorize::auth(const string user, const string key)
{
    if (_accounts[user] != "")
    {
        MD5 md5conv;
        md5conv.update(key);
        return _accounts[user] == md5conv.toString();
    }
    return false;
}

bool
Authorize::addAccount(const string & user, const string & key)
{
    if (_accounts[user] == "")
    {
        MD5 md5conv;
        md5conv.update(key);
        _accounts[user] = md5conv.toString();
        return true;
    }
    return false; 
}

bool
Authorize::delAccount(const string & user)
{
    if (_accounts[user] != "")
    {
        _accounts.erase(_accounts.find(user));
        return true;
    }
    return false; 
}

bool
Authorize::modifyKey(const string & user, const string & newkey)
{
    if (_accounts[user] != "")
    {
        MD5 md5conv;
        md5conv.update(newkey);
        _accounts[user] = md5conv.toString();
        return true;
    }
    return false; 
} 

