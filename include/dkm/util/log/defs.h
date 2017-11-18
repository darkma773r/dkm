#ifndef _DKM_LOG_COMMON_H_
#define _DKM_LOG_COMMON_H_

/**
 * Common definitions for dkm logging.
 */

#include <string>

namespace dkm
{

class Logging;
class Logger;
class LogWriter;

enum class LogLevel 
{
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE
};

struct LogMessage
{
    std::string loggerName;
    int lineNum;
    LogLevel logLevel;

    std::string message;
};

}

#endif