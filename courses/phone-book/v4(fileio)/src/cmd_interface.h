#ifndef __CMD_INTERFACE_PHONEBOOK_H_INCLUDE__
#define __CMD_INTERFACE_PHONEBOOK_H_INCLUDE__


#include <iostream>
#include <iomanip>
#include "book.h"
#include "my_utils.h"
#include "input_control.h"
#include "fileio.h"


using namespace std;

class CmdInterface
{
DEFINE_SINGLETON(CmdInterface)

public:
    void show_fields(const PhoneBook &)const;
    void show(const PhoneBook &)const ;
    void show(const Record &, const vector<string> &)const;
    void show(const RecordList &, const vector<string> &)const;

    static void main_menu();
    static void edit_menu(PhoneBook &);
    static void search_menu(PhoneBook &);
    static void separator();

    static void println(const string &);
    void pause();

private:
    void onAddRecord(PhoneBook &);
    void onEditRecord(PhoneBook &);
    void onSearchRecord(PhoneBook &);
    void onDelRecord(PhoneBook &);
    
    string getLine();
    char getCommand();
    long getNumber();
    bool getConfirmed();

public:
    void run(PhoneBook &);

private:
    InputControl inctrl;
    FileIO file;
};

#endif
