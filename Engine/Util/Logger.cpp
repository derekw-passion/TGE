#include "Logger.h"

namespace TGE
{
    LoggerSettings Logger::LoggerSettings = TGE::LoggerSettings();

    void Logger::Print(const char* message)
    {
        if(LoggerSettings.bLogToFile)
        {
            FILE* file = nullptr;
            if(!fopen_s(&file, LoggerSettings.sLogFile.c_str(), "a"))
            {
                fprintf(file, "%s\n", message);
                fclose(file);
            }

            else
                printf("Failed to open log file for writing\n");
        }
        
        if(LoggerSettings.bPrintToConsole)
            printf("%s\n", message);
    }

    void Logger::Init(TGE::LoggerSettings settings)
    {
        LoggerSettings = settings;
    }

    void Logger::Log(LogLevel level, string format, ...)
    {
        va_list args;
        va_start(args, format);

        string fullMessage;

        if(LoggerSettings.bTimeStamp)
        {
            time_t now = time(0);
            struct tm localTime;
            localtime_s(&localTime, &now);

            char timeString[100];
            strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &localTime);

            fullMessage = "[" + string(timeString) + "]" + LoggerSettings.sDelimiter;
        }

        char buffer[1024];
        vsprintf_s(buffer, format.c_str(), args);
        fullMessage += buffer;

        switch(level)
        {
            case INFO:
                fullMessage = "[INFO]" + LoggerSettings.sDelimiter + fullMessage;
                break;
            case WARNING:
                fullMessage = "[WARNING]" + LoggerSettings.sDelimiter + fullMessage;
                break;
            case ERROR:
                fullMessage = "[ERROR]" + LoggerSettings.sDelimiter + fullMessage;
                break;
        }

        if(LoggerSettings.bPrelude)
            fullMessage = LoggerSettings.sPrelude + LoggerSettings.sDelimiter + fullMessage;

        Print(fullMessage.c_str());
        va_end(args);
    }
} // namespace TGE