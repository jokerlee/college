/*
 * Written By Jackal Dire(jokerleee@gmail.com) 2009.
 */


#ifndef __JACKAL_DIRE_UTILS_H_INCLUDE__
#define __JACKAL_DIRE_UTILS_H_INCLUDE__


/*
 * refuse the copy-constructor and copy-assignment overload
 * added by the compiler silently
 */
#define DEFINE_UNCOPYABLE(Uncopyable) \
private:\
    Uncopyable(const Uncopyable&);\
    Uncopyable & operator=(const Uncopyable &);


/*
 * Singleton in "Design Patterns", this method was invented by
 * Scott Meyers
 */
#define DEFINE_SINGLETON(Singleton) \
public:\
    static Singleton& Instance();\
private:\
    Singleton(){}\
    Singleton(const Singleton&);\
    Singleton & operator=(const Singleton &);\
    ~Singleton(){}

#define IMPLEMENT_SINGLETON(Singleton)\
Singleton & Singleton::Instance() {\
    static Singleton obj;\
    return obj;\
}

#endif
