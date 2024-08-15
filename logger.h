#ifndef __LOGGER__
#define __LOGGER__
#include <fstream>
#include <iostream>
#include <memory>

enum LogLevel {
    INFO = 1,
    DEBUG = 2,
};

class Logger {
    private:
        std::unique_ptr<std::ofstream> logPtr1;
        std::unique_ptr<std::ofstream> logPtr2;
        std::unique_ptr<std::ofstream>* currLogPtr;

        bool isDebugMode;
        int maxFileSize;
        std::string logFileName;
    public:
        Logger(std::string);
        ~Logger();

        std::ofstream& getLogFile();
        void checkLogRollover();

        void writeLog(std::string log, LogLevel logLevel = INFO);
};

#endif
