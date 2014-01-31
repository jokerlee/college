#include "cmd_interface.h"
#include "book.h"


int main(int argc, char *argv[])
{
	PhoneBook pb;
	CmdInterface::Instance().run(pb);    
}
