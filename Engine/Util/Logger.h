#pragma once

#include "../defs.h"
#include <ctime>
#include <string>
#include <cstdarg>

using namespace std;

namespace TGE
{
    struct ENGINE_API LoggerSettings
    {
        bool bPrelude;
        bool bTimeStamp;
        bool bLogToFile;
        bool bPrintToConsole;
        string sLogFile;
        string sPrelude;
        string sDelimiter;

        LoggerSettings()
        {
            bPrelude = true;
            bTimeStamp = false;
            bLogToFile = false;
            bPrintToConsole = true;
            sLogFile = "log.txt";
            sPrelude = "[ENGINE]";
            sDelimiter = " ";
        }
    };

    enum LogLevel
    {
        INFO,
        WARNING,
        ERROR
    };

    class ENGINE_API Logger
    {
    public:
        // Singleton insurance
        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;

    private:
        static LoggerSettings LoggerSettings;

        static void Print(const char* message);
    public:
        static void Init(TGE::LoggerSettings settings);
        static void Log(LogLevel level, string format, ...);
    };
} // namespace TGE