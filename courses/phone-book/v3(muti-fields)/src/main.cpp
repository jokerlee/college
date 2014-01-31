#include "cmd_interface.h"
#include "book.h"

int main(int argc, char *argv[])
{
    vector<string> tags;
    tags.push_back("name");
    tags.push_back("phone");
    tags.push_back("address");

    PhoneBook pb(tags);
	CmdInterface::Instance().run(pb);    
}
