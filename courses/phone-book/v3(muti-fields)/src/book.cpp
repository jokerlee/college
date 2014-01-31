#include "book.h"
#include <iomanip>
#include <algorithm>

/*
 *  Class Record's Implement
 */


Record::Record(string name) : _index(0)
{
    _fields.insert(MapType(name, ""));
}

Record::Record(vector<string> lbls) : _index(0)
{
    for (int i=0; i<lbls.size(); ++i)
    {
        _fields.insert(MapType(lbls[i], ""));
    }
}

Record::operator bool()const
{
	return (*this != empty_record);
}

bool
Record::operator==(const Record & rec)const
{
    if (size() != rec.size())
        return false;
    cMapIter i = _fields.begin();
    for ( ; i != _fields.end(); ++i)
        if (i->second != rec[i->first])
            return false;
    return true;
}

bool
Record::operator!=(const Record & rec)const
{
	return !(rec == *this);
}

string &
Record::operator[](const string & field)
{
    return _fields[field];
}

const string &
Record::operator[](const string & field)const
{
    const FieldMap & m = _fields;
    return (m.find(field))->second;
}

/*
 * Class PhoneBook's Inplement
 */

long PhoneBook::max_index = 1;



PhoneBook::PhoneBook(vector<string> labels)
{
    _labels = labels;
}

void
PhoneBook::addRecord(Record & r)
{
    r.setIndex(max_index++);
    _records.push_back(r);
}

void
PhoneBook::setRecord(const long index, const Record & rec)
{
    ListIter i;
    if ((i=searchIndex(index, _records.begin()))
             != _records.end())
        *i = rec;
}

void
PhoneBook::delRecord(const long index)
{
    ListIter i;
    if ((i=searchIndex(index, _records.begin()))
            != _records.end())
        _records.erase(i);
}

const Record &
PhoneBook::searchByIndex(const long index)
{
    ListIter i;
    if ((i=searchIndex(index, _records.begin()))
             != _records.end())
        return *i;
    else
        return empty_record;
}

RecordList
PhoneBook::searchByField(const string & fd, const string & str)
{
    ListIter i = _records.begin();
    RecordList ret;
    while ((i=searchField(fd, str, i)) != _records.end())
    {
        ret.push_back(*i);
        i++;
    }
    return ret;
}

ListIter
PhoneBook::searchIndex(const long index, ListIter i)
{
    for ( ; i != _records.end(); i++)
        if (i->index()==index)
            return i;
    return i;
}

ListIter
PhoneBook::searchField(const string & lbl, const string & str, ListIter i)
{
    for ( ; i != _records.end(); i++)
        if ((*i)[lbl].find(str) != -1)
            return i;
    return i;
}

void
PhoneBook::refreshIndex()
{
    int j=1;
    ListIter i = _records.begin();
    for ( ; i != _records.end(); i++)
        i->setIndex(j++);
}


