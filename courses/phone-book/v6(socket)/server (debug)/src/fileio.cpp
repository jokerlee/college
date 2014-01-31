#include "fileio.h"
#include <fstream>
#include <vector>

using std::vector;


FileException::FileException(const string & info, const string & opt)
    :_filename(info), _operation(opt)
{

}

string
FileException::what()const
{
    return "Cannot open " + _filename + " to " + _operation + ".";
}

void
FileIO::store(const string & name, const PhoneBook & pb)
{
    ofstream fout(("data/" + name + ".txt").c_str());  
    if (!fout)
        throw FileException("data/" + name + "*.txt", "write");

    fout << pb.recSize() << endl;
    for (int i=0; i<pb.recSize(); ++i)
        fout << pb.field(i) << endl;

    fout << pb.size() << endl;
    cListIter i=pb._records.begin();
    for ( ; i!=pb._records.end(); ++i)
        fout << *i << endl;
     
}

void
FileIO::read(const string & name, PhoneBook * * pb)
{
    ifstream fin(("data/" + name + ".txt").c_str());

    if (!fin)
    {
        ofstream fout(("data/" + name + ".txt").c_str(), ios::out);
        vector<string> fields;
        fields.push_back("name");
        fields.push_back("phone");
        fields.push_back("address");
        *pb = new PhoneBook(fields);

        if (!fout)
            throw FileException("data/" + name + "*.txt", "read");
        fin.close();
        fout.close();
        return;
    }

    string buf;
    int count;

    vector<string> fields;
    fin >> count; fin.get();
    for (int i=0; i<count; ++i)
    {
        getline(fin, buf);
        fields.push_back(buf);
    }
    *pb = new PhoneBook(fields);

    fin >> count;fin.get();
    Record newrec(*(*pb));
    for (int i=0; i<count; ++i)
    {
        fin >> newrec;
        fin.get();
        (*pb)->addRecord(newrec);
    }

    fin.close();
}
