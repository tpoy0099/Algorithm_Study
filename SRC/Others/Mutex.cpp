#include "Mutex.h"

//================================================
//>>> class cMtLock
//================================================
cMtLock::cMtLock() {
    InitializeCriticalSection(&m_MutexLock);
}

cMtLock::~cMtLock() {
    DeleteCriticalSection(&m_MutexLock);
}

bool cMtLock::Lock() {
    EnterCriticalSection(&m_MutexLock);
    return true;
}

bool cMtLock::UnLock() {
    LeaveCriticalSection(&m_MutexLock);
    return true;
}

//================================================
//>>> class cLocker
//================================================

cLocker::cLocker(cMtLock &tLock) {
    tLock.Lock();
    pLock = &tLock;
}

cLocker::~cLocker() {
    pLock->UnLock();
}