#include <iostream>
#include <list>
#include <iterator>
#define MAX 100
using namespace std;

int main()
{
    char tmp[MAX];
    list<string> stack;
    while (cin.getline(tmp, MAX, '#')) stack.push_front(string(tmp));
    copy(stack.begin(),stack.end(),ostream_iterator<string>(cout," "));
}
