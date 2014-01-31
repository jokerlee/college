#include "book.h"
#include <iomanip>
#include <algorithm>

/*
 *  Class Record's Implement
 */


Record::Record(string name) : _index(0)
{

}

Record::operator bool()const
{
	return _labels.size() != 0;
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
    (*this)[name] = content;
}

void
Record::clear()
{
    _data.clear();
}

