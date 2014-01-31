#include "input_control.h"
#include <cctype>

bool
InputControl::isValidNumber(const char ch)
{
    return isdigit(ch);
}

bool
InputControl::isValidNumber(const string & str)
{
    for (int i=0; i<str.size(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

bool
InputControl::isCommand(const string & str)
{
    if (str.size()>1 || !isdigit(str[0]))
        return false;
    return true;
}

long
InputControl::string_to_long(const string & str)
{
	long ret = 0;;
    for (int i=0; i<str.size(); i++)
        ret = ret*10 + str[i] - '0';
    return ret;
}
