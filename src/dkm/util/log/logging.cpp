#include "dkm/util/log/logging.h"

#include <set>

#include "dkm/util/log/logger.h"
#include "dkm/util/log/log_writer.h"

namespace dkm
{

LogLevel Logging::DEFAULT_LOG_LEVEL = LogLevel::INFO;

Logging::Logging() : 
    NonCopyable(),
    mInitialized(false)
{
    mConfig.rootLogLevel = DEFAULT_LOG_LEVEL;
}

Logging::~Logging()
{
}

void Logging::configure(const LoggingConfig& config)
{
    std::lock_guard<std::mutex> lock(mMutex);

    // store the config
    mConfig = config;

    // re-initialize if we've already done that in order
    // to apply the new settings
    if (mInitialized) {
        doInit();
    }
}

void Logging::init() 
{
    std::lock_guard<std::mutex> lock(mMutex);

    doInit();
}

void Logging::registerLogger(Logger* logger)
{
    std::lock_guard<std::mutex> lock(mMutex);

    mLoggers.insert(logger);

    if (mInitialized) {
        // set up this logger now since it's a little
        // late to the party and missed initialization
        initLogger(logger);
    }
}

void Logging::unregisterLogger(Logger* logger)
{
    std::lock_guard<std::mutex> lock(mMutex);

    std::set<Logger*>::iterator it = mLoggers.find(logger);
    if (it != mLoggers.end()) {
        mLoggers.erase(it);
    }
}

void Logging::registerLogWriter(LogWriter* writer)
{
    std::lock_guard<std::mutex> lock(mMutex);

    mWriters.insert(writer);
}

void Logging::unregisterLogWriter(LogWriter* writer)
{
    std::lock_guard<std::mutex> lock(mMutex);

    std::set<LogWriter*>::iterator it = mWriters.find(writer);
    if (it != mWriters.end()) {
        mWriters.erase(it);
    }
}

void Logging::dispatchMessage(const LogMessage& message)
{
    std::lock_guard<std::mutex> lock(mMutex);

    if (!mInitialized) {
        doInit();
    }

    std::set<LogWriter*>::iterator it;
    for (it = mWriters.begin(); it != mWriters.end(); ++it) {
        (*it)->write(message);
    }
}

void Logging::doInit()
{
    std::set<Logger*>::iterator it;

    // initialize each registered logger
    for (it = mLoggers.begin(); it != mLoggers.end(); ++it) {
        initLogger(*it);
    }

    mInitialized = true;
}

void Logging::initLogger(Logger* logger) const
{
    std::map<std::string, LogLevel>::const_iterator entry = 
        mConfig.logLevels.find(logger->getName());
    
    LogLevel level;
    if (entry != mConfig.logLevels.end()) {
        // we have a specific entry so use that
        level = entry->second;
    }
    else {
        // no specific entry found; use the root level
        level = mConfig.rootLogLevel;
    }

    // apply the log level
    logger->setLogLevel(level);
}

void Logging::initLogWriter(LogWriter* writer) const
{

}


}