#ifndef __CMD_INTERFACE_PHONEBOOK_H_INCLUDE__
#define __CMD_INTERFACE_PHONEBOOK_H_INCLUDE__


#include <iostream>
#include <iomanip>
#include "book.h"
#include "my_utils.h"
#include "input_control.h"
#include "fileio.h"


using namespace std;

class ClientProcess
{
private:
    void onAuth(const string);
    void onReg(const string);
    void onIndex(const string);
    void onSetFields(const string, const string);
    void onAddRecord(const string);
    void onEditRecord(const string);
    void onSearchRecord(const string);
    void onDelRecord(const string);
    void onShowAll();
    void store();

    string getNextArg(const string &, int &);
    void send_msg(const char *);

    char * write_msg(const Record &, char * const)const;
    char * write_msg(const RecordList &, char * const)const;
    char * write_record(const Record &, char * const)const;

public:
    ClientProcess();
    ~ClientProcess();
    void run(int);

private:
    int _sockfd;
    InputControl inctrl;
    FileIO file;
    string username;
    PhoneBook * _pb;
    bool _isAuthed;
    bool _isQuit;
    static const int buff_size = 1024;
};

#endif
