#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

typedef enum
{
	LOG_DEBUG = 0,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
} LogLevel;

void setMinLogLevel(LogLevel min);
void vLogLevel(LogLevel l, const char* fmt, va_list args);
void logLevel(LogLevel l, const char* fmt, ...);
void logDebug(const char* fmt, ...);
void logInfo(const char* fmt, ...);
void logWarn(const char* fmt, ...);
void logError(const char* fmt, ...);
void logFatal(const char* fmt, ...);

void printfn(char* fmt, ...);

#endif
#if __INCLUDE_LEVEL__ == 0

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static LogLevel minLogLevel = LOG_DEBUG;

void setMinLogLevel(LogLevel min) { minLogLevel = min; }

void logDebug(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vLogLevel(LOG_DEBUG, fmt, args);
	va_end(args);
}

void logInfo(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vLogLevel(LOG_INFO, fmt, args);
	va_end(args);
}

void logWarn(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vLogLevel(LOG_WARN, fmt, args);
	va_end(args);
}

void logError(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vLogLevel(LOG_ERROR, fmt, args);
	va_end(args);
}

void logFatal(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vLogLevel(LOG_FATAL, fmt, args);
	va_end(args);
}

void vLogLevel(LogLevel l, const char* fmt, va_list args)
{
	if (l < minLogLevel)
	{
		return;
	}
	switch (l)
	{
	case LOG_DEBUG:
		printf("[DEBUG] ");
		break;
	case LOG_INFO:
		printf("[INFO] ");
		break;
	case LOG_WARN:
		printf("[WARN] ");
		break;
	case LOG_ERROR:
	case LOG_FATAL:
		printf("[ERROR] ");
		break;
	}
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
	if (l == LOG_FATAL)
	{
		exit(EXIT_FAILURE);
	}
}

void logLevel(LogLevel l, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vLogLevel(l, fmt, args);
	va_end(args);
}

void printfn(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

#endif
