#ifndef Utility_Mutex_H
#define Utility_Mutex_H

#include <windows.h>

class cMtLock
{
public:
    cMtLock();
    ~cMtLock();

    bool Lock();
    bool UnLock();

private:
    CRITICAL_SECTION m_MutexLock;
};

class cLocker
{
public:
    cLocker(cMtLock &tLock);
    ~cLocker();

private:
    cMtLock *pLock;
};

#endif