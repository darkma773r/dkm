
#ifndef _DKM_LOGGER_H_
#define _DKM_LOGGER_H_

#include <string>
#include <atomic>

#include "dkm/util/noncopyable.h"

#include "dkm/util/log/defs.h"

namespace dkm 
{

/**
 * Primary logging interface. Calling methods on this
 * class dispatches log messages into the logging system.
 * The intended use case is to have an instance of this class
 * declared as a static variable in each compilation unit.
 */ 
class Logger : NonCopyable
{
public:
    Logger(std::string name);

    virtual ~Logger();

    void trace(const char* fmt, ...) const;
    void debug(const char* fmt, ...) const;
    void info(const char* fmt, ...) const;
    void warn(const char* fmt, ...) const;
    void error(const char* fmt, ...) const;

    const std::string& getName() const { return mName; }

    LogLevel getLogLevel() const { return mLogLevel; }
    void setLogLevel(LogLevel logLevel) {
        this->mLogLevel = logLevel;
    }

private:

    std::string mName;

    LogLevel mLogLevel;
}

}

#endif