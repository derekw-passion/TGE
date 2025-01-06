#include "Logger.h"

namespace TGE
{
    LoggerSettings Logger::m_Settings = LoggerSettings();

    void Logger::Print(const char* message)
    {
        if(m_Settings.bLogToFile)
        {
            FILE* file = nullptr;
            if(!fopen_s(&file, m_Settings.sLogFile.c_str(), "a"))
            {
                fprintf(file, "%s\n", message);
                fclose(file);
            }

            else
                printf("Failed to open log file for writing\n");
        }
        
        if(m_Settings.bPrintToConsole)
            printf("%s\n", message);
    }

    void Logger::Init(LoggerSettings settings)
    {
        m_Settings = settings;
    }

    void Logger::Log(LogLevel level, string format, ...)
    {
        va_list args;
        va_start(args, format);

        string fullMessage;

        if(m_Settings.bTimeStamp)
        {
            time_t now = time(0);
            struct tm localTime;
            localtime_s(&localTime, &now);

            char timeString[100];
            strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &localTime);

            fullMessage = "[" + string(timeString) + "]" + m_Settings.sDelimiter;
        }

        char buffer[1024];
        vsprintf_s(buffer, format.c_str(), args);
        fullMessage += buffer;

        switch(level)
        {
            case INFO:
                fullMessage = "[INFO]" + m_Settings.sDelimiter + fullMessage;
                break;
            case WARNING:
                fullMessage = "[WARNING]" + m_Settings.sDelimiter + fullMessage;
                break;
            case ERROR:
                fullMessage = "[ERROR]" + m_Settings.sDelimiter + fullMessage;
                break;
        }

        if(m_Settings.bPrelude)
            fullMessage = m_Settings.sPrelude + m_Settings.sDelimiter + fullMessage;

        Print(fullMessage.c_str());
        va_end(args);
    }
} // namespace TGE