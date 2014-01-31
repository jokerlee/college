#include "fileio.h"
#include <fstream>
#include <vector>

using std::vector;


FileException::FileException(const string & info)
    :_filename(info)
{

}

string
FileException::what()const
{
    return _filename + " cannot be opened.";
}

void
FileIO::store(const PhoneBook & pb)
{
    ofstream fout("a.txt");
    
    if (!fout) throw FileException("a.txt");

    fout << pb.recSize() << endl;
    for (int i=0; i<pb.recSize(); ++i)
        fout << pb.field(i) << endl;

    fout << pb.size() << endl;
    cListIter i=pb._records.begin();
    for ( ; i!=pb._records.end(); ++i)
        fout << *i << endl;
}

void
FileIO::read(PhoneBook & pb)
{
    ifstream fin("a.txt");
    string buf;
    int count;

    vector<string> fields;
    fin >> count; fin.get();
    for (int i=0; i<count; ++i)
    {
        getline(fin, buf);
        fields.push_back(buf);
    }
    pb.setFields(fields);

    fin >> count;fin.get();
    Record newrec(pb);
    for (int i=0; i<count; ++i)
    {
        fin >> newrec;
        fin.get();
        pb.addRecord(newrec);
    }

    fin.close();
}
