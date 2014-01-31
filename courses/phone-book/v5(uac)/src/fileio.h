#ifndef __FILEIO_PHONEBOOK_H_INCLUDE__
#define __FILEIO_PHONEBOOK_H_INCLUDE__

#include "book.h"

class FileIO
{
public:
    void store(const string &, const PhoneBook & pb);
    void read(const string &, PhoneBook & pb);
};


class FileException
{
public:
    FileException(const string & name, const string & opt);
    string what()const;

private:
    string _filename;
    string _operation;
};

#endif
