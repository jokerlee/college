#ifndef __CMD_INTERFACE_H_INCLUDE__
#define __CMD_INTERFACE_H_INCLUDE__


#include <iostream>
#include <iomanip>
#include "book.h"
#include "my_utils.h"

using namespace std;

class CmdInterface
{
DEFINE_SINGLETON(CmdInterface)

public:
    static void show(const Record &);
    static void show(const PhoneBook &);
    static void show(const RecordList &);
    static void main_menu();

public:
    void run(PhoneBook &);

private:
    void addRecord(PhoneBook &);
    void editRecord();
    void searchRecord();
    void delRecord();
};

#endif
