#include "cmd_interface.h"
#include "auth.h"
#include <cstdio>
#include <cstdlib>
#include <termio.h>



int getch(void)
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


/* 
 * class Display's Implement
 */
IMPLEMENT_SINGLETON(CmdInterface)

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
        
            if (Authorize::Instance().auth(buf1, buf2))
            {
                username = buf1;
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
                    if (Authorize::Instance().addAccount(buf1, buf2))
                        cout << "rigister successfully.\n";
                    else
                        cout << "user name have been rigistered.\n";
                    break;
                }
                else
                    cout << "two passwords don't match! type again.\n";
            } 
        }
        else if (cmd == 0)
                exit(0);
        else
            cout << "Error command;" << endl;
    }
}


void
CmdInterface::println(const string & str)
{
    cout << str << endl;
}

void
CmdInterface::separator()
{
    cout << "=====================================================" << endl;
}

void
CmdInterface::show_fields(const PhoneBook & pb)const
{
    cout << left << setw(5)  << "No";
    for (int i=0; i<pb.recSize(); ++i)
        cout << left << setw(15) << pb.field(i);
    cout << endl;
}

void
CmdInterface::show(const Record & rec, const vector<string> & lbls)const
{
   cout << left << setw(5)  << rec.index();
   for (int i=0; i<lbls.size(); ++i)
       cout << left << setw(15) << rec[lbls[i]];
   cout << endl;
}  

void
CmdInterface::show(const PhoneBook & pb)const
{
    if (pb._records.size() != 0)
    {
        show_fields(pb);
        CmdInterface::show(pb._records, pb.fields());
    }
    else
        println("empty.");
}

void
CmdInterface::show(const RecordList & lst, const vector<string> & lbls)const
{
    if (lst.size() > 0)
    {
        cListIter i = lst.begin();
        for ( ; i != lst.end(); i++)
            CmdInterface::show(*i, lbls);
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
CmdInterface::search_menu(PhoneBook & pb)
{
    for (int i=0; i<pb.recSize(); ++i)
        cout << "(" << i+1 << ")" << "Search " << pb.field(i) << " ";
    cout << "(0)Cancel" << endl;
}

void
CmdInterface::edit_menu(PhoneBook & pb)
{
    for (int i=0; i<pb.recSize(); ++i)
        cout << "(" << i+1 << ")" << "Edit " << pb.field(i) << " ";
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
CmdInterface::onAddRecord(PhoneBook & pb)
{
    println("=====================Add Record======================");
    Record newrec(pb);
    string tmp;
    for (int i=0; i<pb.recSize(); ++i)
    {
        cout << pb.field(i);
        newrec[pb.field(i)] = getLine();
    }
    pb.addRecord(newrec);
    show_fields(pb);
    show(newrec, pb.fields());
    println("Record successfully added.");
}


void
CmdInterface::onEditRecord(PhoneBook & pb)
{
    println("====================Edit Record=====================");
    long index = -1;
    Record tmp;
    println("Input the record's index to Edit(0 to cancel)");
    if ((index = getNumber()) != 0)
    {
        if (tmp = pb.searchByIndex(index))
        {
            println("The record is");
            show_fields(pb);
            show(tmp, pb.fields());
            edit_menu(pb);
            int cmd;
            do{ 
                cmd = getNumber();
                if (cmd > 0 && cmd < pb.recSize())
                {
                    cout << "Input the new " << pb.field(cmd-1);
                    tmp[pb.field(cmd-1)] = getLine();
                    cout << pb.field(cmd-1) << " successfully modified." << endl;
                }
                else
                    println("Error Command!");
                edit_menu(pb);
            }while (cmd != 0);
            pb.setRecord(index, tmp);
            show_fields(pb);
            show(tmp, pb.fields());
            cout << "Record #" << index << " updated." << endl;
        }
        else
            println("Index not found!");
    }
    else
        println("Canceled"); 
}

void
CmdInterface::onSearchRecord(PhoneBook & pb)
{
    println("===================Search Record===================");    
    search_menu(pb);
    int cmd = getNumber();
    if (cmd > 0 && cmd < pb.recSize())
    {
        cout << pb.field(cmd-1);
        show(pb.searchByField(pb.field(cmd-1), getLine()),
                pb.fields());
    }
    else
        println("Error Command!");
}

void
CmdInterface::onDelRecord(PhoneBook & pb)
{
    println("===================Delete Record===================");
    long index=-1;
    Record tmp;
    println("Input the record's index to delete(0 to cancel)");
    if ((index = getNumber()) != 0)
    {
        if (tmp = pb.searchByIndex(index))
        {
            println("The record is ");
            show_fields(pb);
            show(tmp, pb.fields());
            println("Are you sure to delete it? (y/n)");
            if (getConfirmed())
            {
                pb.delRecord(index);
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
    while((ch = getch())!= -1 && ch != ENTER)
    {
        if(i == MAX_LEN && ch != BACKSPACE)
            continue;
        if(ch == BACKSPACE)
        {
            if(i==0)
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

    if(ch == -1)
    {
        while(i != -1)
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

void
CmdInterface::run(PhoneBook & pb)
{
    authorize();
    cout << "          Phone Book 0.1 By JackalDire          \n";
    
    main_menu();
    
    try {
        file.read(username, pb);
    } catch (const FileException & e) {
        cerr << e.what() << endl;
    }

    int cmd;
    do
    {
        cmd = getNumber();
        switch (cmd)
        {
            case 1: onAddRecord(pb); pause(); main_menu();break;
            case 2: onEditRecord(pb); pause(); main_menu();break;
            case 3: onSearchRecord(pb); pause(); main_menu();break;
            case 4: onDelRecord(pb); pause(); main_menu();break;
            case 5: show(pb); pause(); main_menu();break;
            case 9: main_menu(); break;
            case 0: cout << "Exit.\n"; break;
            default:
                cout << "Error Command!\n";
                cin.clear();
                cin.sync();
                break;
        }
    }
    while(cmd != 0);

    try {
        file.store(username, pb);
    } catch (const FileException & e) {
        cerr << e.what() << endl;
    }
}
