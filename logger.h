#ifndef __LOGGER__
#define __LOGGER__
#include <fstream>
#include <iostream>
#include <memory>

using namespace std;
enum LogLevel {
    INFO = 1,
    DEBUG = 2,
};

class Logger {
    private:
        unique_ptr<ofstream> logPtr1;
        unique_ptr<ofstream> logPtr2;
        unique_ptr<ofstream>* currLogPtr;

        bool isDebugMode;
        int maxFileSize;
        string logFileName;
    public:
        Logger(string);
        ~Logger();

        ofstream& getLogFile();
        void checkLogRollover();

        void writeLog(string log, LogLevel logLevel = INFO);
};


#endif
