/**
 * simple_log.h
 * 
 * Contains macros for logging to the console. To use, define
 * the value DKM_LOG_LEVEL and include this header file. Allowed
 * values are 0 = NONE, 1 = ERROR, 2 = WARN, 3 = INFO, and 
 * 4 = DEBUG. By default, log messages include file names and
 * line numbers. To disable this feature, define the value
 * DKM_LOG_NO_LINE_NUM.
 */

#ifndef _DKM_SIMPLE_LOG_H_
#define _DKM_SIMPLE_LOG_H_

#include <time.h>
#include <stdio.h>

/*
Create a macro for showing the current time unless we were
told not to.
*/
#ifndef DKM_LOG_NO_TIME
	#define _DKM_LOG_TIME(os) \
		unsigned int __ms; \
		struct tm* __tm; \
		struct timespec __ts;	\
		clock_gettime(CLOCK_REALTIME, &__ts);\
		__ms = (unsigned int)(__ts.tv_nsec / 1000000); \
		__tm = localtime(&__ts.tv_sec); \
		fprintf(os, "[%04d-%02d-%02d %02d:%02d:%02d.%03d] ", __tm->tm_year + 1900, \
			__tm->tm_mon + 1, __tm->tm_mday, __tm->tm_hour, __tm->tm_min, \
			__tm->tm_sec, __ms); 
#else
	#define _DKM_LOG_TIME(os)
#endif

/* 
Create a macro for showing the line numbers unless we were
told not to. 
*/
#ifndef DKM_LOG_NO_LINE_NUM
	/* use double expansion macros to get the line number as a string */
	#define _DKM_STR(x) #x
	#define DKM_STR(x) _DKM_STR(x)
	#define _DKM_LOG_LINE_NUM "(" __FILE__ ", line " DKM_STR(__LINE__) ") "
#else
	#define _DKM_LOG_LINE_NUM
#endif

/* Set a default log level of warning */
#ifndef DKM_LOG_LEVEL
	#define DKM_LOG_LEVEL 2
#endif

/* Create some macro flags for testing log levels */
#if DKM_LOG_LEVEL >= 1
	#define DKM_ERROR_ENABLED
#endif

#if DKM_LOG_LEVEL >= 2
	#define DKM_WARN_ENABLED
#endif

#if DKM_LOG_LEVEL >= 3
	#define DKM_INFO_ENABLED
#endif

#if DKM_LOG_LEVEL >= 4
	#define DKM_DEBUG_ENABLED
#endif

/* Create the actual logging macros */
#ifdef DKM_ERROR_ENABLED
    #define DKM_ERROR(...) \
		do { \
			_DKM_LOG_TIME(stderr) \
			fprintf(stderr, "[ERROR] " _DKM_LOG_LINE_NUM); \
			fprintf(stderr, __VA_ARGS__ ); \
			fprintf(stderr, "\n"); \
		} while(0)
#else
    #define DKM_ERROR(...)
#endif

#ifdef DKM_WARN_ENABLED
    #define DKM_WARN(...) \
		do { \
			_DKM_LOG_TIME(stderr) \
			fprintf(stderr, "[WARN] " _DKM_LOG_LINE_NUM); \
			fprintf(stderr, __VA_ARGS__ ); \
			fprintf(stderr, "\n"); \
		} while(0)
#else
    #define DKM_WARN(...)
#endif

#ifdef DKM_INFO_ENABLED
    #define DKM_INFO(...)\
		do { \
			_DKM_LOG_TIME(stdout) \
			fprintf(stdout, "[INFO] " _DKM_LOG_LINE_NUM); \
			fprintf(stdout, __VA_ARGS__ ); \
			fprintf(stdout, "\n"); \
		} while(0)
#else
    #define DKM_INFO(...)
#endif

#ifdef DKM_DEBUG_ENABLED
    #define DKM_DEBUG(...) \
		do { \
			_DKM_LOG_TIME(stdout) \
			fprintf(stdout, "[DEBUG] " _DKM_LOG_LINE_NUM); \
			fprintf(stdout, __VA_ARGS__ ); \
			fprintf(stdout, "\n"); \
		} while(0)
#else
    #define DKM_DEBUG(...)
#endif

#endif // end header guard
