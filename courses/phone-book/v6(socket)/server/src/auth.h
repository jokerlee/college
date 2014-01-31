#ifndef __AUTHORIZE_PHONEBOOK_H_INCLUDE__
#define __AUTHORIZE_PHONEBOOK_H_INCLUDE__

#include <iostream>
#include <map>
#include "my_utils.h"

using namespace std;

class Authorize
{
DEFINE_UNCOPYABLE(Authorize)

public:
    static Authorize & Instance(){
        static Authorize obj;
        return obj;
    }
public:
    void readData();
    bool addAccount(const string &, const string &);
    bool delAccount(const string &);
    bool modifyKey(const string &,  const string &);
    bool auth(const string, const string);

private:
    Authorize();
    ~Authorize();
    void updateData();
    map<string, string> _accounts;
    string _file;
};

#endif
