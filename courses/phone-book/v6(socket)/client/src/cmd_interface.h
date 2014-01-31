#ifndef __CMD_INTERFACE_PHONEBOOK_H_INCLUDE__
#define __CMD_INTERFACE_PHONEBOOK_H_INCLUDE__


#include <iostream>
#include <iomanip>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>

#include "book.h"
#include "my_utils.h"
#include "input_control.h"


using namespace std;

class CmdInterface
{
DEFINE_SINGLETON(CmdInterface)

public:
    void show();
    void show(const Record &)const;
    void show(const RecordList &)const;
    void show_fields()const;

    void main_menu();
    void edit_menu();
    void search_menu();
    void separator();

    void println(const string &)const;
    void pause();

private:
    void authorize();
    void onAddRecord();
    void onSetFields();
    void onEditRecord();
    void onSearchRecord();
    void onDelRecord();
    void onQuit();

    void send_rqst(string);
    bool recv_rslt();
    bool recv_rslt(string &);

    RecordList read_list(const char * const)const;
    Record read_record(const char *, int &)const;

    string getNextArg(const string &, int &)const;
    string getNextArg(const char * const, int &)const;

    int getch();
    string getLine();
    string getPassword();
    long getNumber();
    bool getConfirmed();

public:
    void run(int);

    static const int MAX_LEN = 12;
    static const int BACKSPACE = 127;
    static const int ENTER = 13;
    


private:
    vector<string> _lbls;
    InputControl inctrl;
    string username;
    int _sockfd;
};

#endif
