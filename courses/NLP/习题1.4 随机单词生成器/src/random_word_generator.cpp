/* Title : random word generator for Zipf's Law
 * Author : Joker Lee
 * Date : Oct, 2009
 * @ BUPT
 * lisence : GLPv3
 * Email : jokerleee@gmail.com
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;

struct Word
{
    string word;
    size_t freq;
    Word(string w, size_t s)
    {
        word = w;
        freq = s;
    }
};

struct ltword
{
    bool operator()(Word s1, Word s2) const
    {
        return s1.freq <= s2.freq;
    }
};


class RandWordGen
{
/* inner data */
private:
    char _letters[27];
    map<string, size_t> _dict;
    vector<size_t> _stats;
    set<Word, ltword> _ranklst;

/* inner methods*/
private:
    char _rand_letter() { return _letters[rand()%27]; };
    string _generate_word();

/* interface */
public:
    RandWordGen(int mlen = 300);
    void start(int max, int len);
    void build_dictionary(int max);
    void statistics();
    void show_stats(int len, ostream & out = cout);
};


/* =================================================== *
 *          Class RandWordGen's Implementaion          *
 * =================================================== */

typedef map<string, size_t>::iterator mIter;
typedef set<Word, ltword>::reverse_iterator sIter;

RandWordGen::RandWordGen(int mlen /*=1000*/)
{
    srand(time(NULL));
    _stats.resize(mlen);
    strcpy(_letters, " abcdefghijklmnopqrstuvwxyz");
}

void
RandWordGen::build_dictionary(int max)
{
    string word;
    size_t orig_size;

    for (int i = 0; i < max; ++i)
    {
        word = _generate_word();
        if (word.size() < _stats.size())
        {
            orig_size = _dict.size();
            _dict[word]++;
            if (_dict.size() != orig_size)
                _stats[word.size()] ++;
        }
    }
}

string
RandWordGen::_generate_word()
{
    string word;
    char ch;

    while ((ch = _rand_letter()) == ' ');
    word.push_back(ch);
    while ((ch = _rand_letter()) != ' ')
        word.push_back(ch);

    return word;
}

void
RandWordGen::statistics()
{
    for (mIter i = _dict.begin(); i != _dict.end(); ++i)
    {
        _ranklst.insert(Word(i->first, i->second));
    }
}

void
RandWordGen::show_stats(int len, ostream& out /*=cout*/)
{
    /*for (int i = 0; i < _stats.size(); ++i)
        out << setw(3) << i << ":" << _stats[i] << endl; */

    int rank = 1;
    for (sIter i = _ranklst.rbegin(); rank < len && i != _ranklst.rend(); ++i)
    {
        out << rank++ << "\t" << i->freq << "\t" << i->word << endl;
    }

}

void
RandWordGen::start(int max, int len)
{
    build_dictionary(max);
    statistics();
    ofstream os("result.txt", ios::out);
    show_stats(len, os);
}


/* end of class RandWordGen's implementation */

int str2int(char * str)
{
    int num = 0;
    while (*str)
    {
        num = num * 10 + *str - '0';
        str++;
    }
    return num;
}


int main(int argc, char * argv[])
{
    int max = 100000, len = 300;
    RandWordGen * obj = new RandWordGen();
    if (argc > 1)   max = str2int(argv[1]);
    if (argc > 2)   len = str2int(argv[2]);
    obj->start(max, len);

    return 0;
}
