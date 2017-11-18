/**
 * log.h
 * 
 * Basic logging system. 
 */

 #ifndef _DKM_LOG_H_
 #define _DKM_LOG_H_

#include <string>

#include 
namespace dkm
{

class Logger : NonCopyable
{
public:
    Logger();

    virtual ~Logger() { }

    void trace(const char* fmt, ...);
    void debug(const char* fmt, ...);
    void info(const char* fmt, ...);
    void warn(const char* fmt, ...);
    void error(const char* fmt, ...);

private:

    std::string mName;
    std::string mFileName;
}

class Logging : NonCopyable
{
public:
    static Logging& getInstance();

    Logging();
}

}

 #endif