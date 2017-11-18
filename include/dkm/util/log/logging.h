#ifndef _DKM_LOGGING_H_
#define _DKM_LOGGING_H_

#include <mutex>
#include <set>

#include "dkm/util/noncopyable.h"

#include "dkm/util/log/defs.h"

namespace dkm
{

class Logging : NonCopyable
{
public:
    /**
     * Returns a reference to the global logging instance.
     */
    static Logging& getInstance();

    Logging();

    virtual ~Logging();

    void registerLogger(Logger* logger);
    void unregisterLogger(Logger* logger);

    void registerLogWriter(LogWriter* writer);
    void unregisterLogWriter(LogWriter* writer);

    void dispatchMessage(const LogMessage& message);

private:
    std::mutex mMutex;

    std::set<Logger*> mLoggers;
    std::set<LogWriter*> mWriters;
};

}

#endif