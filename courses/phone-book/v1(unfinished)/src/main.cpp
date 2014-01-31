#include "book.h"
#include "cmd_interface.h"

long PhoneBook::max_index = 1;

int main()
{
    PhoneBook pb;
    CmdInterface::Instance().run(pb);

    return 0;
}
