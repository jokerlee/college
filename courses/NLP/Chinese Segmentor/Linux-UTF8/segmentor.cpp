#include <iostream>
#include <fstream>
#include <iterator>
#include <clocale>
#include <hash_map>
#include <list>
#include <map>

using namespace std;
using namespace __gnu_cxx;

wchar_t pucts[] = {L'，', L'：', L'、', L'。', L'！', L'？', L'；'};
wchar_t nums[] = {L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',
                    L'一', L'二', L'三', L'四', L'五', L'六', L'七', L'八', L'九', L'〇', L'十'};
wchar_t in_nums[] = {L'.', L'点', L'十', L'百', L'千', L'万', L'兆', L'亿', L'／'};
wchar_t date[] = {L'年', L'月', L'日', L'时', L'分', L'秒'};
wchar_t alpha[] = {L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J', L'L', L'L', L'M', 
        L'N', L'O', L'P', L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X', L'Y', L'Z', 
        L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l', L'm', 
        L'n', L'o', L'p', L'q', L'r', L's', L't', L'u', L'v', L'w', L'x', L'y', L'z'};

class hash_func
{
public:
	size_t operator()(const wstring & s)const
    {
        unsigned long val = 0;
        for (int i = 0; i < s.size(); ++i)
            val = val*16 + s[i];
        return size_t(val);
    }
};

class Dictionary
{
public:
    Dictionary(const string & f);
    void loadDictionary(const string & f);
    bool isDate(const wstring & word);
    bool isNumeric(const wstring & word);
    bool isEnglish(const wstring & word);
    double freq(const wstring & word);
    int operator[](const wstring & word);

private:
    hash_map<wstring, float, hash_func> _dict;
    map<wchar_t, int> _special;

public:
    static const int NUM = 1;
    static const int INNUM = 2;
    static const int DATE = 3;
    static const int ALPHA = 4;
};

Dictionary::Dictionary(const string & f)
{
    loadDictionary(f);

    for (int i = 0; i < sizeof(nums)/sizeof(nums[0]); ++i)
        _special[nums[i]] = NUM;

    for (int i = 0; i < sizeof(in_nums)/sizeof(in_nums[0]); ++i)
        _special[in_nums[i]] = INNUM;
    
    for (int i = 0; i < sizeof(date)/sizeof(date[0]); ++i)
        _special[date[i]] = DATE;
        
    for (int i = 0; i < sizeof(alpha)/sizeof(alpha[0]); ++i)
        _special[alpha[i]] = ALPHA;
}

void
Dictionary::loadDictionary(const string & f)
{
	wifstream fin(f.c_str());
    fin.imbue(std::locale(""));

    wstring word;
    float freq = 0;

    wcout << L"loading dictionary..." << endl;
	
    fin >> word >> freq;
    while (fin)
    {
        _dict[word] = freq;    
		fin >> word >> freq;
    }
    
    fin.close();
    wcout << L"finished, " 
          << "Totally " << _dict.size() << " words." << endl;
}

bool
Dictionary::isNumeric(const wstring & word)
{
    if (_special[word[0]] != NUM)
        return false;

    for (int i = 1; i < word.size(); ++i)
        if (!_special[word[i]])
            return false;
    
    return true;
}

bool
Dictionary::isDate(const wstring & word)
{
    if (_special[word[word.size() - 1]] != DATE)
        return false;

    for (int i = 0; i < word.size() - 1; ++i)
        if (_special[word[i]] != NUM)
            return false;
    return true;
}


bool
Dictionary::isEnglish(const wstring & word)
{ 
    for (int i = 0; i < word.size(); ++i)
        if (_special[word[i]] != ALPHA)
            return false;
    return true;
}

double
Dictionary::freq(const wstring & word)
{
    if (!_dict[word]) return 0;
    else return _dict[word];
}


int
Dictionary::operator[](const wstring & word)
{
    return word.size() == 1 || isDate(word) || isEnglish(word) 
            || isNumeric(word) || _dict[word];
}

class Normalizer
{
public:
    Normalizer(wistream & in, wostream & out);
    void process();

private:
    map<wchar_t, wchar_t> _nrmltbl;
    wistream & _is;
    wostream & _os;
};

Normalizer::Normalizer(wistream & in, wostream & out)
    : _is(in), _os(out)
{
    _is.imbue(std::locale(""));
    _os.imbue(std::locale(""));

    wifstream fin("normalize_table.dat");
    fin.imbue(std::locale(""));

    wstring s;
    fin >> s;
    while (fin)
    {
        for (int i = 1; i < s.size(); ++i)
            _nrmltbl[s[i]] = s[0];
        fin >> s;
    }

    fin.close();
}

void
Normalizer::process()
{
    wchar_t c;
    _is.get(c); // not use _is >> c, _is will ignore blank and newline
    while (_is)
    {
        if (_nrmltbl[c] != 0) _os << _nrmltbl[c];
        else _os << c;
        _is.get(c);
    }
}


class Segmenter
{
public:
    Segmenter(wistream & in, wostream & out, const string & f);
    void DocumentToSentence(); 
    void SentenceToWord(const wstring & sentence);

private:
    Dictionary _dict;
    map<wchar_t, int> _stops;
    wistream & _is;
    wostream & _os;
};


Segmenter::Segmenter(wistream & in, wostream & out, const string & f)
    : _dict(f.c_str()), _is(in), _os(out)
{
    _is.imbue(std::locale(""));
    _os.imbue(std::locale(""));
    
    for (int i = 0; i < sizeof(pucts)/sizeof(pucts[0]); ++i)
        _stops[pucts[i]] = 1;
}

void
Segmenter::DocumentToSentence()
{
    wstring stc;
    wchar_t c;
    size_t cnt = 0;

    _is.get(c);
    while (_is)
    {
        if (_stops[c] == 1 || cnt > 100)
        {
            SentenceToWord(stc);
            _os << c << " ";
            stc.clear();
            cnt = 0;
        }
        else
            stc += c, cnt++;
        
        _is.get(c);
    }
    if (stc.size()) SentenceToWord(stc);
    
}

void
Segmenter::SentenceToWord(const wstring & stc)
{
    typedef list<wstring>::iterator lIter;

    list<wstring> words;
    wstring remain = stc;
    while (remain.size())
    {
        int i = remain.size();
        for ( ;i && _dict[remain.substr(0, i)] == 0; --i)
            ;
        words.push_back(remain.substr(0, i));
        remain = remain.substr(i, remain.size() - i);
    }

    list<wstring> rwords;
    remain = stc;
    while (remain.size())
    {
        int i = 0;
        int s = remain.size();
        for ( ; i < s && _dict[remain.substr(i, s - i)] == 0; ++i)
            ;
        rwords.push_front(remain.substr(i, s - i));
        remain = remain.substr(0, i);
    }
    
    double s(1), t(1);
    if (words != rwords)
    {
        lIter i = words.begin();
        lIter j = rwords.begin();
        for ( ; *i == *j; ++i, ++j)
            ;
        
        lIter p = --words.end();
        lIter q = --rwords.end();
        for ( ; *p == *q; --p, --q)
            ;

        for (lIter m = i; m != p; ++m)
            s += _dict.freq(*m);
        s += _dict.freq(*p);

        for (lIter n = j; n != q; ++n)
            t += _dict.freq(*n);
        t += _dict.freq(*q);
        
        /* output conflicts 
        if (s && t)
        {
            for ( ; i != p; ++i) _os << *i << " ";
            _os << *p << " " << s;
            if (s >= t) _os << " (preferred)";
            _os << endl;

            for ( ; j != q; ++j) _os << *j << " ";
            _os << *q << " " << t;
            if (s < t) _os << " (preferred)";
            _os << endl;
            _os << endl;
        }*/

    }
    if (t > s) words = rwords;
    for (lIter i = words.begin();
            i != words.end(); ++i)
        _os << *i << " ";
    
}
int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "");

    wofstream tmpout("segtmp.dat");
    Normalizer nrm(wcin, tmpout);
    nrm.process();
    tmpout.close();

    wifstream tmpin("segtmp.dat");

    string dict = "dict.dat";
    if (argc > 1)
        dict = argv[1];
    Segmenter seg(tmpin, wcout, dict);

    seg.DocumentToSentence();
    tmpin.close();

    return 0;
}
