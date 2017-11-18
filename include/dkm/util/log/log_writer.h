#ifndef _DKM_LOG_APPENDER_H_
#define _DKM_LOG_APPENDER_H_

#include "dkm/util/noncopyable.h"

#include "dkm/util/log/defs.h"

namespace dkm
{

/**
 * Interface for classes that write log messages
 * to an output destination.
 */
class LogWriter : NonCopyable 
{
public:
    virtual ~LogWriter();

    virtual void write(const LogMessage& message) = 0;
};

}

#endif