#ifndef __BOOK_H_INCLUDE__
#define __BOOK_H_INCLUDE__

#include "my_utils.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;
/*
class Name
{
    Name(string first, string last)
    {   
        
    }
    string _firstname;
    string _lastname;
    bool isCh;

}*/

class Record
{

private:
    string _name;
    string _phone;
    string _addr;    
    long _index;

public:
    Record();
    Record(string name, string phone="(empty)", string addr="(empty)");
    
    operator bool()const;
    bool operator==(const Record &)const;
    bool operator!=(const Record & rec)const;

    long index()const { return _index; }
    const string & name()const { return _name; }
    const string & phone()const { return _phone; }
    const string & addr()const { return _addr; }

    void setIndex(long index) { _index = index; }
    void setName(const string & name) { _name = name; }
    void setPhone(const string & phone) { _phone = phone; }
    void setAddr(const string & addr) { _addr = addr; }
    
};

typedef list<Record> RecordList;
typedef list<Record>::iterator Iter;
typedef list<Record>::const_iterator cIter;




class PhoneBook
{
friend class CmdInterface;

private: 
    static long max_index;

protected:
    RecordList _records;

public:
    void addRecord(Record &);
    void delRecord(const long);
    void setRecord(const long, const Record &);
    const Record & searchByIndex(long index);
    RecordList searchByName(const string &);
    RecordList searchByPhone(const string &);

private:
    Iter searchName(const string &, Iter);
    Iter searchIndex(const long, Iter);
    Iter searchPhone(const string &, Iter);
    
    void refreshIndex();
};


const Record empty_record("", "", "");

#endif
