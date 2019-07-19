#ifndef _SYSTEM_LOCKABLE_H_
#define _SYSTEM_LOCKABLE_H_

#include <System/Base/Types.h>

interface ILockable
{
    bool Lock(u32 timeout = 0);
    void Unlock();
};

struct LockableLocker
{
    ILockable* lockable;

    LockableLocker(ILockable* lockable) : lockable(lockable)
    {
        lockable->Lock();
    }
    LockableLocker(ILockable& lockable) : lockable(&lockable)
    {
        lockable.Lock();
    }
    ~LockableLocker()
    {
        lockable->Unlock();
    }
};

#endif