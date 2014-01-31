#ifndef __CMD_INPUT_CONTROL_PHONEBOOK_H_INCLUDE__
#define __CMD_INPUT_CONTROL_PHONEBOOK_H_INCLUDE__

#include <iostream>

using std::string;

class InputControl
{
public:
    bool isValidNumber(const char)const;
    bool isValidNumber(const string &)const;
	bool isCommand(const string &)const;
	long string_to_long(const string &)const;
    const string long_to_string(long)const;
};

#endif
