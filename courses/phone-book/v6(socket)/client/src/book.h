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


class Record
{

private:
    map<string, string> _data;
    long _index;
    vector<string> _labels;

public:
    Record(const string = "");

    operator bool()const;
    bool operator==(const Record &)const;
    bool operator!=(const Record &)const;
    string & operator[](const string &);
    const string & operator[](const string &)const;

    const long index()const { return _index; }
    const long size()const { return _data.size(); }
    
    void clear();
    void setIndex(long index) { _index = index; }
    void setField(const string &, const string &);
    
};

typedef list<Record> RecordList;
typedef RecordList::iterator ListIter;
typedef RecordList::const_iterator cListIter;


#endif
