#ifndef __BOOK_PHONEBOOK_H_INCLUDE__
#define __BOOK_PHONEBOOK_H_INCLUDE__

#include "my_utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

typedef map<string, string> FieldMap;
typedef FieldMap::iterator MapIter;
typedef FieldMap::const_iterator cMapIter;
typedef map<string, string>::value_type MapType;

class PhoneBook;

class Record
{

private:
    map<string, string> _data;
    long _index;
    const PhoneBook * _owner;

public:
    Record(string name="");
    Record(const PhoneBook &);

    const PhoneBook * owner()const { return _owner; }
    operator bool()const;
    bool operator==(const Record &)const;
    bool operator!=(const Record &)const;
    string & operator[](const string &);
    const string & operator[](const string &)const;

    friend ostream & operator<<(ostream & out, const Record & );
    friend istream & operator>>(istream & out, Record & );

    const long index()const { return _index; }
    const long size()const { return _data.size(); }
    
    void clear();
    void attach(const PhoneBook & pb) { _owner = &pb; }
    void setIndex(long index) { _index = index; }
    void setField(const string &, const string &);
    
};

typedef list<Record> RecordList;
typedef RecordList::iterator ListIter;
typedef RecordList::const_iterator cListIter;




class PhoneBook
{
friend class CmdInterface;
friend class FileIO;

private: 
    static long max_index;
    vector<string> _labels;

protected:
    RecordList _records;

public:
    PhoneBook(vector<string>);
    
    void setFields(vector<string>);
    vector<string> fields()const { return _labels; }
    const string field(long n)const { return _labels[n]; }

    long size()const { return _records.size(); }
    long recSize()const { return _labels.size(); }
    
    void addRecord(Record &);
    void delRecord(const long);
    void setRecord(const long, const Record &);
    const Record & searchByIndex(long index);
    RecordList searchByField(const string &, const string &);
    RecordList getList(){ return _records;  }

private:
    ListIter searchIndex(const long, ListIter);
    ListIter searchField(const string &, const string &, ListIter);
    
    void refreshIndex();
};


const Record empty_record("");

#endif
