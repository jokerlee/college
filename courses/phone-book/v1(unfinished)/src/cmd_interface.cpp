#include "cmd_interface.h"

/* 
 * class Display's Implement
 */

IMPLEMENT_SINGLETON(CmdInterface)

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
        cout << "empty.\n";
}

void
CmdInterface::show(const RecordList & lst)
{
    cIter i = lst.begin();
    for ( ; i != lst.end(); i++)
        CmdInterface::show(*i);
}

void
CmdInterface::main_menu()
{
    cout << "(1)Add a record" << endl
         << "(2)Edit a record" << endl
         << "(3)Search" << endl
         << "(4)Remove a record" << endl
         << "(5)List all records" << endl
         << "(9)Show main menu" << endl
         << "(0)Exit" << endl;
}

void
CmdInterface::addRecord(PhoneBook & pb)
{
    Record newrec("");
    string tmp;
    cin.ignore();
    cout << "Input the person's name:" << endl;
    newrec.setName((getline(cin, tmp), tmp));
    cout << "Input the phone number:" << endl;
    newrec.setPhone((getline(cin, tmp), tmp));
    cout << "Input the address:" << endl;
    newrec.setAddr((getline(cin, tmp), tmp));

    pb.addRecord(newrec);
    cout <<"Record successfully added.\n";
}


void
CmdInterface::editRecord()
{

}

void
CmdInterface::searchRecord()
{

}

void
CmdInterface::delRecord()
{

}

void
CmdInterface::run(PhoneBook & pb)
{
    cout << "==============Phone Book 0.1 By JackalDire==============\n";
    
    main_menu();

    string cmd;
    do
    {
        cout << "cmd>";
        cin >> cmd;
        if (cmd.size() > 1)
        {
            cout << "Error Command!\n";
            cin.clear();
            cin.sync();
            cmd[0] = 1;
            continue;
        }

        switch (cmd[0])
        {
            case '1': addRecord(pb); main_menu(); break;
            case '2': editRecord(); main_menu(); break;
            case '3': searchRecord(); main_menu(); break;
            case '4': delRecord(); main_menu(); break;
            case '5': show(pb); main_menu(); break;
            case '9': main_menu(); break;
            case '0': cout << "Exit.\n"; break;
            default:
                cout << "Error Command!\n";
                cin.clear();
                cin.sync();
                break;

        }
    }
    while(cmd[0] != '0');
}
