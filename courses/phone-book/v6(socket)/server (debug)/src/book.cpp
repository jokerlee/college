#include "book.h"
#include <iomanip>
#include <algorithm>

ostream & operator<<(ostream & out, const Record & rec)
{
    if (rec.size() != 0 && rec.owner())
        for (int i=0; i != rec.size(); ++i) 
            out << rec[rec.owner()->field(i)] << ","; 
    return out;
}

istream & operator>>(istream & in, Record & rec)
{
    if (in && rec.owner())
    {
        string buf;
        for (int i=0; i<rec.owner()->recSize(); ++i)
        {
            getline(in, buf, ',');
            rec[rec.owner()->field(i)] = buf;
        }
    }
    return in;
}


/*
 *  Class Record's Implement
 */


Record::Record(string name) : _index(0), _owner(0)
{
    _data.insert(MapType("name", name));
}

Record::Record(const PhoneBook & pb) : _index(0), _owner(0)
{
    _owner = &pb;
    for (int i=0; i<pb.recSize(); ++i)
    {
        _data.insert(MapType(pb.field(i), ""));
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
    cMapIter i = _data.begin();
    for ( ; i != _data.end(); ++i)
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
    return _data[field];
}

const string &
Record::operator[](const string & field)const
{
    const FieldMap & m = _data;
    return (m.find(field))->second;
}

void
Record::setField(const string & name, const string & content)
{
    if ((*this)[name] != "")
        (*this)[name] = content;
    else
        _data.insert(MapType(name, content));
}

void
Record::clear()
{
    _data.clear();
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
PhoneBook::setFields(vector<string> labels)
{
    _labels = labels;
}

void
PhoneBook::addRecord(Record & r)
{
    r.setIndex(max_index++);
    r.attach(*this);
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
    while ((i=searchField(fd, str, ++i)) != _records.end())
        ret.push_back(*i);
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


