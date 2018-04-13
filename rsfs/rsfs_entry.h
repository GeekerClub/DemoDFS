// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#ifndef  GUNIR_TERA_ENTRY_H
#define  GUNIR_TERA_ENTRY_H

#include "toft/system/threading/mutex.h"

namespace rsfs {

class GunirEntry {
public:
    GunirEntry();
    virtual ~GunirEntry();

    virtual bool Start();
    virtual bool Run();
    virtual bool Shutdown();

protected:
    virtual bool StartServer() = 0;
    virtual void ShutdownServer() = 0;

private:
    bool ShouldStart();
    bool ShouldShutdown();

private:
    toft::Mutex m_mutex;
    bool m_started;
};

}  // namespace rsfs

#endif  // GUNIR_TERA_ENTRY_H
