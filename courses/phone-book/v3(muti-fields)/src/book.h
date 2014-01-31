#ifndef __BOOK_H_INCLUDE__
#define __BOOK_H_INCLUDE__

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

class Record
{

private:
    map<string, string> _fields;
    long _index;

public:
    Record(string name="");
    Record(vector<string>);

    operator bool()const;
    bool operator==(const Record &)const;
    bool operator!=(const Record &)const;
    string & operator[](const string &);
    const string & operator[](const string &)const;

    const long index()const { return _index; }
    const long size()const { return _fields.size(); }

    void setIndex(long index) { _index = index; }
    void setField(const string &, long);
    
};

typedef list<Record> RecordList;
typedef RecordList::iterator ListIter;
typedef RecordList::const_iterator cListIter;




class PhoneBook
{
friend class CmdInterface;

private: 
    static long max_index;
    vector<string> _labels;

protected:
    RecordList _records;

public:
    PhoneBook(vector<string>);
    vector<string> fields()const { return _labels; }
    const string field(long n)const { return _labels[n]; }
    long recSize()const { return _labels.size(); }
    void addRecord(Record &);
    void delRecord(const long);
    void setRecord(const long, const Record &);
    const Record & searchByIndex(long index);
    RecordList searchByField(const string &, const string &);

private:
    ListIter searchIndex(const long, ListIter);
    ListIter searchField(const string &, const string &, ListIter);
    
    void refreshIndex();
};


const Record empty_record("");

#endif
