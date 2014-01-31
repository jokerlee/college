#include "cmd_interface.h"

/* 
 * class Display's Implement
 */

IMPLEMENT_SINGLETON(CmdInterface)

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
        cout << "(" << i+1 << ")" << "Search" << pb.field(i) << " ";
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
    Record newrec(pb.fields());
    string tmp;
    for (int i=0; i<pb.recSize(); ++i)
    {
        cout << pb.field(i) << ": ";
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
    println("Input the record's index to Edit(0 to cancel):");
    if ((index = getNumber()) != 0)
    {
        if (tmp = pb.searchByIndex(index))
        {
            println("The record is: ");
            show_fields(pb);
            show(tmp, pb.fields());
            edit_menu(pb);
            int cmd;
            do{
                cmd = getNumber();
                if (cmd > 0 && cmd < pb.recSize())
                {
                    cout << "Input the new " << pb.field(cmd-1) << ": ";
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
        cout << pb.field(cmd-1) << ": ";
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
    println("Input the record's index to delete(0 to cancel):");
    if ((index = getNumber()) != 0)
    {
        if (tmp = pb.searchByIndex(index))
        {
            println("The record is: ");
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
    string ret;
    do
    {
        cin.clear();
        cin.sync();
    }
    while((getline(cin, ret), ret) == "");
    return ret;
}

char
CmdInterface::getCommand()
{
    string cmd = getLine();
    while (cmd.size() > 1 || !inctrl.isValidNumber(cmd))
    {
        println("Error command!");
        cmd = getLine();
    }
    return cmd[0];
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
    cout << "          Phone Book 0.1 By JackalDire          \n";
    
    main_menu();

    int cmd;
    do
    {
        cout << "cmd>";
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
}
