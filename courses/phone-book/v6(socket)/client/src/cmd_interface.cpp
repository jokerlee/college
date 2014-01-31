
#include <cstdio>
#include <cstdlib>
#include <termio.h>

#include "cmd_interface.h"

string sptr("\001");
/* 
 * class Display's Implement
 */
IMPLEMENT_SINGLETON(CmdInterface)

string
CmdInterface::getNextArg(const string & cmd, int & pos)const
{
    char buff[512];
    sscanf(cmd.c_str()+pos, "%[^\001]", buff);
    pos += strlen(buff) + 1;
    return buff;
}

string
CmdInterface::getNextArg(const char * const p, int & pos)const
{
    char buff[512];
    sscanf(p+pos, "%[^\001]", buff);
    pos += strlen(buff) + 1;
    return buff;
}

void
CmdInterface::send_rqst(const string cmd)
{
    printf("%s\n", cmd.c_str());
    send(_sockfd, cmd.c_str(), cmd.size()+1, 3);
}

bool
CmdInterface::recv_rslt()
{
    char buff[1024];
    recv(_sockfd, buff, 1024, 0);
    if (strncmp(buff, "false", 5) == 0)
        return false;
    else
        return true;
}

bool
CmdInterface::recv_rslt(string & rslt)
{
    char buff[1024];
    recv(_sockfd, buff, 1024, 0);
    if (strncmp(buff, "false", 5) == 0)
    {
        rslt = "";
        return false;
    }
    else
    {
        rslt = buff;
        return true;
    }
}

Record
CmdInterface::read_record(char const * p, int & pos)const
{
    Record rec;
    char buff[1024];

    rec.setIndex(inctrl.string_to_long(getNextArg(p, pos)));
    for (int i=0; i<_lbls.size(); ++i)
    {
        memset(buff, 0, sizeof(buff));
        rec[_lbls[i]] = getNextArg(p, pos);
    }
    return rec;
}


RecordList
CmdInterface::read_list(const char * const str)const
{
    RecordList lst;
    const char * p = str;
    int count = 0, pos = 0;

    count = inctrl.string_to_long(getNextArg(p, pos));
    for (int i=0; i<count; ++i)
        lst.push_back(read_record(p, pos));
    return lst;
}

void
CmdInterface::authorize()
{
    string buf1, buf2, buf3;
    while (true)
    {
        cout << "(1)login (2)rigister (0)Exit" << endl;
        int cmd = getNumber();
        if (cmd == 1)
        {
            cout << "user name";
            buf1 = getLine();
            cout << "password";
            buf2 = getPassword();
            
            send_rqst("AUTH " + buf1 + sptr + buf2.c_str());
            if (recv_rslt(buf3))
            {
                username = buf1;
                int count = 0, pos=0;
                count = inctrl.string_to_long(getNextArg(buf3, pos));
                for (int i=0; i < count; i++)
                    _lbls.push_back(getNextArg(buf3, pos));
                println("login successfully.\n");
                break;
            }
            else
                cout << "login failed.\n";
        }
        else if (cmd == 2)
        {
            cout << "new user name";
            buf1 = getLine();
            while (true)
            {
                cout << "new password";
                buf2 = getPassword();
                cout << "confirm password";
                buf3 = getPassword();
                if (buf2 == buf3)
                {
                    send_rqst("REG " + buf1 + sptr + buf2.c_str());
                    if (recv_rslt())
                    {
                        cout << "rigister successfully.\n";
                        onSetFields();
                    }
                    else
                        cout << "user name have been rigistered.\n";
                    break;
                }
                else
                    cout << "two passwords don't match! type again.\n";
            } 
        }
        else if (cmd == 0)
        {
            send_rqst("QUIT");
            exit(0);
        }
        else
            cout << "Error command;" << endl;
    }
}

void
CmdInterface::onSetFields()
{
    cout << "Set your phone book's fields." << endl
         << "eg. \"name\", \"phone\" etc. \"0\" to finish." << endl;
    string tmp = getLine(), buff;
    int count = 0;
    vector<string> fields;
    while (tmp != "0")
    {
        fields.push_back(tmp);
        buff += tmp + sptr;
        tmp = getLine();
        count ++;
    }
    send_rqst("FIELD " + inctrl.long_to_string(count) + sptr + buff);
}

void
CmdInterface::println(const string & str)const
{
    cout << str << endl;
}

void
CmdInterface::separator()
{
    cout << "=====================================================" << endl;
}

void
CmdInterface::show_fields()const
{
    cout << left << setw(5)  << "No";
    for (int i=0; i<_lbls.size(); ++i)
        cout << left << setw(15) << _lbls[i];
    cout << endl;
}

void
CmdInterface::show()
{
    send_rqst("ALL");
    string buff;
    show_fields();
    if (recv_rslt(buff))
        show(read_list(buff.c_str()));
}

void
CmdInterface::show(const Record & rec)const
{
   cout << left << setw(5)  << rec.index();
   for (int i=0; i<_lbls.size(); ++i)
       cout << left << setw(15) << rec[_lbls[i]];
   cout << endl;
}  

void
CmdInterface::show(const RecordList & lst)const
{
    if (lst.size() > 0)
    {
        cListIter i = lst.begin();
        for ( ; i != lst.end(); i++)
            CmdInterface::show(*i);
    }
    else
        println("empty.");
}

void
CmdInterface::main_menu()
{
    println("Main Menu");
    separator();
    println("(1)Add record\t\t(4)Remove record");
    println("(2)Edit record\t\t(5)List all records");
    println("(3)Search record\t(9)Show main menu");
    println("(0)Exit");
    separator();
}

void
CmdInterface::search_menu()
{
    for (int i=0; i<_lbls.size(); ++i)
        cout << "(" << i+1 << ")" << "Search " << _lbls[i] << " ";
    cout << "(0)Cancel" << endl; 
}

void
CmdInterface::edit_menu()
{
    for (int i=0; i<_lbls.size(); ++i)
        cout << "(" << i+1 << ")" << "Edit " << _lbls[i] << " ";
    cout << "(0)Cancel" << endl;
}

void
CmdInterface::pause()
{
    cin.clear();
    cin.sync();
    println("(Enter to continue.)");
    cin.get();
}
    
void
CmdInterface::onAddRecord()
{
    println("=====================Add Record======================");
    Record newrec;
    string tmp;
    string buf = "ADD ";
    for (int i=0; i<_lbls.size(); ++i)
    {
        cout << _lbls[i];
        buf = buf + getLine() + sptr;
    }

    send_rqst(buf);
    if (recv_rslt())
    {
        println("Record successfully added.");
    }
}

void
CmdInterface::onEditRecord()
{
    long index = -1;
    string buff;
    
    println("====================Edit Record=====================");
    println("Input the record's index to Edit(0 to cancel)");
    if ((index = getNumber()) != 0)
    {
        send_rqst("INDEX " + inctrl.long_to_string(index) + sptr);
        if (recv_rslt(buff))
        {
            println("The record is");
            show_fields();
            show(read_list(buff.c_str()));

            edit_menu();
            int cmd;
            do{
                cmd = getNumber();
                if (cmd > 0 && cmd <= _lbls.size())
                {
                    cout << "Input the new " << _lbls[cmd-1];
                    send_rqst("EDIT " + inctrl.long_to_string(index) + sptr
                              + _lbls[cmd-1] + sptr + getLine());
                    if (recv_rslt())
                        cout << _lbls[cmd-1] << " successfully modified." << endl;
                }
                else
                    println("Error Command!");
                edit_menu();
            }while (cmd != 0);
            cout << "Record #" << index << " updated." << endl;
        }
        else
            println("Index not found!");
    }
    else
        println("Canceled"); 
}

void
CmdInterface::onSearchRecord()
{
    println("===================Search Record===================");    
    search_menu();

    int cmd = getNumber();
    string buff;

    if (cmd > 0 && cmd <= _lbls.size())
    {
        cout << _lbls[cmd-1];
        send_rqst("QUERRY " + _lbls[cmd-1] + sptr + getLine() + sptr );
        if (recv_rslt(buff))
            show(read_list(buff.c_str()));
    }
    else
        println("Error Command!");
}

void
CmdInterface::onQuit()
{
    send_rqst("QUIT");
}

void
CmdInterface::onDelRecord()
{
    println("===================Delete Record===================");
    long index=-1;
    Record tmp;
    string buff;
    println("Input the record's index to delete(0 to cancel)");
    if ((index = getNumber()) != 0)
    {
        send_rqst("INDEX " + inctrl.long_to_string(index) + sptr);
        if (recv_rslt(buff))
        {
            println("The record is ");
            show_fields();
            show(read_list(buff.c_str()));
            println("Are you sure to delete it? (y/n)");
            if (getConfirmed())
            {
                send_rqst("DEL " + inctrl.long_to_string(index) + sptr);
                if (recv_rslt())
                cout << "Record successfully deleted.\n";
            }
            else
                println("Canceled");
        }
        else
            println("Index not found!");
    }
    else
        println("Canceled");       
}

string
CmdInterface::getLine()
{
    cout << ": ";
    string ret;
    do
    {
        cin.clear();
        cin.sync();
    }
    while((getline(cin, ret), ret) == "");
    return ret;
}

long
CmdInterface::getNumber()
{
    string ret = getLine();
    while (!inctrl.isValidNumber(ret))
    {
        println("Not a valid number! Pleas enter a number(0 to cancel).");
        ret = getLine();
    }
    return inctrl.string_to_long(ret);
}

string CmdInterface::getPassword() 
{
    int i=0, ch;
    string p = "";
    cout << ": ";
    while ((ch = getch())!= -1 && ch != ENTER)
    {
        if (i == MAX_LEN && ch != BACKSPACE)
            continue;
        if(ch == BACKSPACE)
        {
            if (i == 0)
                continue;
            i--;
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }
        else
        {
            p[i++] = ch;
            putchar('*');
        }
    }

    if (ch == -1)
    {
        while (i != -1)
            p[i--] = '\0';
        return NULL;
    }
    p[i]='\0';
    putchar('\n');
    return p;    
}


bool
CmdInterface::getConfirmed()
{
    string input = getLine();
    while (true)
    {
        if (input == "Y" || input == "y")
            return true;
        if (input == "N" || input == "n")
            return false;
        else
            println("(y/n)");
    }
}

int 
CmdInterface::getch(void)
{
        struct termios tm, tm_old;
        int fd = STDIN_FILENO, c;
        if(tcgetattr(fd, &tm) < 0)
                return -1;
        tm_old = tm;
        cfmakeraw(&tm);
        if(tcsetattr(fd, TCSANOW, &tm) < 0)
                return -1;
        c = fgetc(stdin);
        if(tcsetattr(fd, TCSANOW, &tm_old) < 0)
                return -1;
        return c;
}



void
CmdInterface::run(int sockfd)
{
    _sockfd = sockfd;
    authorize();
    cout << "          Phone Book 0.1 By JackalDire          \n";
    
    main_menu();
    
    int cmd;
    do
    {
        cmd = getNumber();
        switch (cmd)
        {
            case 1: onAddRecord(); pause(); main_menu();break;
            case 2: onEditRecord(); pause(); main_menu();break;
            case 3: onSearchRecord(); pause(); main_menu();break;
            case 4: onDelRecord(); pause(); main_menu();break;
            case 5: show(); pause(); main_menu();break;
            case 9: main_menu(); break;
            case 0: onQuit(); cout << "Exit.\n"; break;
            default:
                cout << "Error Command!\n";
                cin.clear();
                cin.sync();
                break;
        }
    }
    while(cmd != 0);
}
