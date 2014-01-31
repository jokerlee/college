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
CmdInterface::show(const Record & rec)
{
   cout << left << setw(5)  << rec.index()
        << left << setw(15) << rec.name()
        << left << setw(15) << rec.phone()
        << left << setw(20) << rec.addr() << endl;
}

void
CmdInterface::show(const PhoneBook & pb)
{
    if (pb._records.size() != 0)
    {
        cout << left << setw(5)  << "No"
             << left << setw(15) << "Name"
             << left << setw(15) << "Phone"
             << left << setw(15) << "Address" << endl;
        CmdInterface::show(pb._records);
    }
    else
        println("empty.");
}

void
CmdInterface::show(const RecordList & lst)
{
    if (lst.size() > 0)
    {
        cIter i = lst.begin();
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
CmdInterface::edit_menu()
{
    println("(1)Modify name (2)Modify phone (3)Modify Address (0)Finish");
}

void
CmdInterface::pause()
{
    cin.clear();
    cin.sync();
    println("Enter to continue.");
    cin.get();
}
    
void
CmdInterface::onAddRecord(PhoneBook & pb)
{
    Record newrec("");
    string tmp;
    println("Input the person's name:");
    newrec.setName(getLine());
    println("Input the phone number:");
    newrec.setPhone(getLine());
    println("Input the address:");
    newrec.setAddr(getLine());

    pb.addRecord(newrec);
    println("Record successfully added.");
}


void
CmdInterface::onEditRecord(PhoneBook & pb)
{
    long index = -1;
    Record tmp;
    println("Input the record's index to Edit(0 to cancel):");
    if ((index = getNumber()) != 0)
    {
        if (tmp = pb.searchByIndex(index))
        {
            println("The record is: ");
            show(tmp);
            edit_menu();
            char cmd;
            do{
                cmd = getCommand();
                switch (cmd)
                {
                    case '1': 
                        println("Input the new name:");
                        tmp.setName(getLine());
                        println("Name successfully modified.");
                        break;

                    case '2': 
                        println("Input the new phone:");
                        tmp.setPhone(getLine());
                        println("Phone successfully modified.");
                        break;

                    case '3': 
                        println("Input the new address:");
                        tmp.setAddr(getLine()); 
                        println("Address successfully modified.");
                        break;
                    case '0': println("Finish Modification."); break;
                    default : println("Error Command!"); break;
                }
                edit_menu();
            }while (cmd != '0');
            pb.setRecord(index, tmp);
            cout << "Record #" << index << " successfully modified." << endl;
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
    println("(1)Search index (2)Search name (3)Search phone");
    char cmd;
    cmd = getCommand();
    switch(cmd)
    {
        case '1':
            long index;
            println("Input the index to search:");
            if ((index = getNumber()) != 0)
            {
                Record tmp;
                if (tmp = pb.searchByIndex(index))
                {
                    show(tmp);
                }
                else
                    println("Index not found!");
            }
            else
                println("Canceled");
            break;

        case '2':
            println("Input the name to search:");
            show(pb.searchByName(getLine()));
            break;

        case '3':
            println("Input the phone to search:");
            show(pb.searchByPhone(getLine()));
            break;

        case '0': println("Canceled"); break;
        default : println("Error command."); break;
    }
}

void
CmdInterface::onDelRecord(PhoneBook & pb)
{
    long index=-1;
    Record tmp;
    println("Input the record's index to delete(0 to cancel):");
    if ((index = getNumber()) != 0)
    {
        if (tmp = pb.searchByIndex(index))
        {
            println("The record is: ");
            show(tmp);
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
    cin.clear();
    cin.sync();
    string ret;
    return (getline(cin, ret), ret);
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

    char cmd;
    do
    {
        cout << "cmd>";
        cmd = getCommand();
        switch (cmd)
        {
            case '1': onAddRecord(pb); pause(); main_menu();break;
            case '2': onEditRecord(pb); pause(); main_menu();break;
            case '3': onSearchRecord(pb); pause(); main_menu();break;
            case '4': onDelRecord(pb); pause(); main_menu();break;
            case '5': show(pb); pause(); main_menu();break;
            case '9': main_menu(); break;
            case '0': cout << "Exit.\n"; break;
            default:
                cout << "Error Command!\n";
                cin.clear();
                cin.sync();
                break;
        }
    }
    while(cmd != '0');
}
