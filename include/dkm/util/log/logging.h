#ifndef _DKM_LOGGING_H_
#define _DKM_LOGGING_H_

#include <set>
#include <map>
#include <vector>
#include <atomic>
#include <mutex>

#include "dkm/util/noncopyable.h"

#include "dkm/util/log/defs.h"

namespace dkm
{

struct LoggingConfig 
{
public:
    /**
     * The root log level. This is applied to all loggers
     * not specifically mentioned in the logLevels map.
     */
    LogLevel rootLogLevel;

    /**
     * Map of logger names to log levels.
     */
    std::map<std::string, LogLevel> logLevels;
};

class Logging : NonCopyable
{
public:
    /**
     * Returns a reference to the global logging instance.
     */
    static Logging& getInstance();

    /**
     * The default log level. This is used when nothing
     * else is configured.
     */
    static LogLevel DEFAULT_LOG_LEVEL;

    Logging();

    virtual ~Logging();

    void configure(const LoggingConfig& config);

    void init();

    const LoggingConfig& getConfig() const;

    void registerLogger(Logger* logger);
    void unregisterLogger(Logger* logger);

    void registerLogWriter(LogWriter* writer);
    void unregisterLogWriter(LogWriter* writer);

    void dispatchMessage(const LogMessage& message);

private:

    void doInit();
    void initLogger(Logger* logger) const;
    void initLogWriter(LogWriter* writer) const;

    std::mutex mMutex;
    bool mInitialized;

    std::set<Logger*> mLoggers;
    std::set<LogWriter*> mWriters;

    LoggingConfig mConfig;
};

}

#endif