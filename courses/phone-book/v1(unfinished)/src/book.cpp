#include "book.h"
#include <iomanip>
#include <algorithm>

/*
 *  Class Record's Implement
 */
Record::Record(string name, string phone, string addr)
    : _name(name), _phone(phone), _addr(addr), _index(0)
{
    
}

/*
class CheckMatch
{
private:
    string _str;
    int _flg;
public:
    CheckMatch(string str, int flag): _str(str), _flg(flag)
    { 
    
    }
    
    bool operator()(Record &x) const
    {
        if (_flg == 1 && x.name().find(_str) != -1
         || _flg == 2 && x.phone().find(_str) != -1
         || _flg == 3 && x.addr().find(_str) != -1 )
            return false;
        else
            return true;
    }

};
*/

/*
 * Class PhoneBook's Inplement
 */

void
PhoneBook::addRecord(Record & r)
{
    r.setIndex(max_index++);
    _records.push_back(r);
}

void
PhoneBook::setRecord(long index, const Record & rec)
{
    Iter i;
    if ((i=searchIndex(index, _records.begin()))
             != _records.end())
        *i = rec;
}

void
PhoneBook::delByName(const string & name)
{
    Iter i;
    if ((i=searchName(name, _records.begin()))
             != _records.end())
        _records.erase(i);
}

void
PhoneBook::delByPhone(const string & phone)
{
    Iter i;
    if ((i=searchPhone(phone, _records.begin()))
             != _records.end())
        _records.erase(i);
}

const Record &
PhoneBook::searchByIndex(const long index)
{
    Iter i;
    if ((i=searchIndex(index, _records.begin()))
             != _records.end())
        return *i;
}

RecordList
PhoneBook::searchByName(const string & name)
{
    Iter i = _records.begin(), j;
    RecordList ret;
    while ((j=searchName(name, i)) != _records.end())
        ret.push_back(*j);
    return ret;
}

RecordList
PhoneBook::searchByPhone(const string & phone)
{
    Iter i = _records.begin(), j;
    list<Record> ret;
    while ((j=searchPhone(phone, i)) != _records.end())
        ret.push_back(*j);
    return ret;
}

Iter
PhoneBook::searchIndex(const long index, Iter i)
{
    for ( ; i != _records.end(); i++)
        if (i->index()==index)
            return i;
    return i;
}

Iter
PhoneBook::searchName(const string & name, Iter i)
{
    for ( ; i != _records.end(); i++)
        if (i->name().find(name) != -1)
            return i;
    return i;
}


Iter
PhoneBook::searchPhone(const string & phone, Iter i)
{
    for ( ; i != _records.end(); i++)
        if (i->phone().find(phone) != -1)
            return i;
    return i;
    /*return find_if(_records.begin(), _records.end(), CheckMatch(phone, 2));*/
}


void
PhoneBook::refreshIndex()
{
    int j=1;
    Iter i = _records.begin();
    for ( ; i != _records.end(); i++)
        i->setIndex(j++);
}


