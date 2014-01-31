#include "client_process.h"
#include "auth.h"
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>

string sptr = "\001";
/* 
 * class Display's Implement
 */


ClientProcess::ClientProcess()
{
    _pb = 0;
}

ClientProcess::~ClientProcess()
{
    if (_pb)
    {
        delete _pb;
        _pb = 0;
    }
}

string
ClientProcess::getNextArg(const string & cmd, int & pos)
{
    char buff[512];
    sscanf(cmd.c_str()+pos, "%[^\001]", buff);
    pos += strlen(buff) + 1;
    return buff;
}

void
ClientProcess::onAuth(const string cmd)
{
    string name, key;
    int pos = 0;
    name = getNextArg(cmd, pos);
    key = getNextArg(cmd, pos);

    if (Authorize::Instance().auth(name, key))
    {
        _isAuthed = true;

        try {
            file.read(name, &_pb);
        } catch (const FileException & e) {
            send_msg("false cannot read the file");
        }

        string buff = inctrl.long_to_string(_pb->recSize())+sptr;
        for (int i=0; i<_pb->recSize(); ++i)
            buff += _pb->field(i) + sptr;
        send_msg(buff.c_str());         
    }
    else
        send_msg("false");
}

void
ClientProcess::onReg(const string cmd)
{
    string name, key;
    int pos = 0;
    name = getNextArg(cmd, pos);
    key = getNextArg(cmd, pos);

    if (Authorize::Instance().addAccount(name, key))
        send_msg("true");
    else
        send_msg("false");
}

void
ClientProcess::onAddRecord(const string cmd)
{
    string tmp;
    Record newrec(*_pb);

    for (int i=0, pos=0; i<_pb->recSize(); ++i)
    {
        tmp = getNextArg(cmd, pos);
        newrec[_pb->field(i)] = tmp;
    }
    _pb->addRecord(newrec);
    send_msg("true");
}

void
ClientProcess::onIndex(const string cmd)
{
    int pos = 0;
    long index = inctrl.string_to_long(getNextArg(cmd, pos));
    Record tmp;
    if (tmp = _pb->searchByIndex(index))
    {
        char buf[buff_size];
        write_msg(tmp, buf);
    }
    else
        send_msg("false");
}

void
ClientProcess::onEditRecord(const string cmd)
{
    int pos = 0;
    Record tmp;
    long index = inctrl.string_to_long(getNextArg(cmd, pos));
    if (tmp = _pb->searchByIndex(index))
    {
        char buf[buff_size];
        long field = inctrl.string_to_long(getNextArg(cmd, pos));
        tmp[_pb->field(field)] = getNextArg(buf, pos);
        _pb->setRecord(index, tmp);
        write_msg(tmp, buf);
        send_msg(buf);
    }
    else
        send_msg("false");
}

void
ClientProcess::onSearchRecord(const string cmd)
{
    int pos = 0;
    long field = inctrl.string_to_long(getNextArg(cmd, pos));
    string content = getNextArg(cmd, pos);
    
    if (field > 0 && field < _pb->recSize())
    {
        char buf[buff_size];
        write_msg(_pb->searchByField(_pb->field(field), content), buf);
    }
    else
        send_msg("false");
}

void
ClientProcess::onDelRecord(const string cmd)
{
    int pos = 0;
    long index = inctrl.string_to_long(getNextArg(cmd, pos));
    Record tmp;
    if (tmp = _pb->searchByIndex(index))
    {
        _pb->delRecord(index);
        send_msg("true");
    }
    else
        send_msg("false");
}

void
ClientProcess::onShowAll()
{
    char buff[1024];
    write_msg(_pb->getList(), buff);
    send_msg(buff);
}

void
ClientProcess::send_msg(const char * buf)
{
    send(_sockfd, buf, strlen(buf)+1, 0);
}


void
ClientProcess::run(int sockfd)
{
    _sockfd = sockfd;
    char buf[1024];
    int ret;
    do
    {
        RecordList lst;
        for (int i=0; i<10; i++)
        {
        Record tmp; 
        vector<string> fields;
        fields.push_back("name");
        fields.push_back("phone");
        fields.push_back("address");
        _pb = new PhoneBook(fields);
        tmp[(string)"name"] = "jackal";
        tmp[(string)"phone"] = "1234";
        tmp[(string)"address"] = "asassa";
        lst.push_back(tmp);
        }

        write_msg(lst, buf);
        bzero(&buf, sizeof(buf));
        ret = recv((int)sockfd, buf, 1024, 0);
        if (ret > 0)
        {
            printf("%s\n", buf);
            
            if (strncmp(buf, "AUTH", 4) == 0)
                onAuth(buf+5);
            else if (strncmp(buf, "REG", 3) == 0)
                onReg(buf+4);
            else if (strncmp(buf, "QUERRY", 6) == 0)
                onSearchRecord(buf+7);
            else if (strncmp(buf, "ADD", 3) == 0)
                onAddRecord(buf+4);
            else if (strncmp(buf, "DEL", 3) == 0)
                onDelRecord(buf+4);
            else if (strncmp(buf, "INDEX", 5) == 0)
                onIndex(buf+6);
            else if (strncmp(buf, "QUIT", 4) == 0)
                break;
            else if (strncmp(buf, "ALL", 3) == 0)
                onShowAll();
            sleep(1);
        }
    }while(true);

    try {
        file.store(username, *_pb);
    } catch (const FileException & e) {
        cerr << e.what() << endl;
    }
}



char *
ClientProcess::write_msg(const Record & rec, char * const buff)const
{
    char * p = buff;

    p += sprintf(p, "%d%s", rec.index(), sptr.c_str());
    for (int i=0; i<rec.size(); ++i)
        p += sprintf(p, "%s%s", rec[_pb->field(i)].c_str(), sptr.c_str());

    return p;
}

char *
ClientProcess::write_msg(const RecordList & lst, char * const buff)const
{
    char * p = buff;
    
    p += sprintf(p, "%d%s", lst.size(), sptr.c_str());

    cListIter i = lst.begin();
    for ( ; i != lst.end(); ++i)
        p = write_msg(*i, p);
    *p = 0;
    return p;
}
