#ifndef __FILEIO_PHONEBOOK_H_INCLUDE__
#define __FILEIO_PHONEBOOK_H_INCLUDE__

#include "book.h"

class FileIO
{
public:
    void store(const PhoneBook & pb);
    void read(PhoneBook & pb);
};


class FileException
{
public:
    FileException(const string & name);
    string what()const;

private:
    string _filename;
};
#endif
