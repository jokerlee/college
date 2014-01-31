#ifndef __CMD_INTERFACE_H_INCLUDE__
#define __CMD_INTERFACE_H_INCLUDE__


#include <iostream>
#include <iomanip>
#include "book.h"
#include "my_utils.h"
#include "input_control.h"

using namespace std;

class CmdInterface
{
DEFINE_SINGLETON(CmdInterface)

public:
    static void show(const Record &);
    static void show(const PhoneBook &);
    static void show(const RecordList &);
    static void main_menu();
    static void edit_menu();
    static void separator();
    static void println(const string &);
    void pause();

public:
    void run(PhoneBook &);

private:
    void onAddRecord(PhoneBook &);
    void onEditRecord(PhoneBook &);
    void onSearchRecord(PhoneBook &);
    void onDelRecord(PhoneBook &);
    
    string getLine();
    char getCommand();
    long getNumber();
    bool getConfirmed();
private:
    InputControl inctrl;
};

#endif
