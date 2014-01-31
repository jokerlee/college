#ifndef __CMD_INPUT_CONTROL_H_INCLUDE__
#define __CMD_INPUT_CONTROL_H_INCLUDE__

#include <iostream>

using std::string;

class InputControl
{
public:
    bool isValidNumber(const char);
    bool isValidNumber(const string &);
	bool isCommand(const string &);
	long string_to_long(const string &);
};

#endif
