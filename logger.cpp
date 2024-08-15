#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <memory>
#include "logger.h"

using namespace std;

ofstream&
Logger::getLogFile()
{
    return **currLogPtr;
}

void
Logger::checkLogRollover()
{
    if(getLogFile().tellp() >= maxFileSize)
    {
        cout << "Max file size reached. Rolling over\n";

        if(currLogPtr == &logPtr1)
        {
            logPtr1->close();
            logPtr2 = make_unique<ofstream>(ofstream(logFileName + "002.log", ios::trunc));
            currLogPtr = &logPtr2;
        }
        else
        {
            logPtr2->close();
            logPtr1 = make_unique<ofstream>(ofstream(logFileName + "001.log", ios::trunc));
            currLogPtr = &logPtr1;
        }
    }
}

Logger::Logger(string fileName)
{
    logFileName = fileName;
    logPtr1 = make_unique<ofstream>(ofstream(logFileName + "001.log", ios::app)); // TODO open 2 if 1 is full?

    currLogPtr = &logPtr1;

    char* level = getenv("LOGLEVEL");

    if(level)
    {
        if(strcmp(level, "DEBUG") == 0)
            isDebugMode = true;
        else
            isDebugMode = false;
    }

    if(!getLogFile().is_open())
    {
        cout << "ERROR could not open log file\n";
        assert(1);
    }

    maxFileSize = 1024 * 1024;
    writeLog("Initialized log");
}

Logger::~Logger()
{
    if(logPtr1 && logPtr1->is_open())
    {
        logPtr1->close();
    }

    if(logPtr2 && logPtr2->is_open())
    {
        logPtr2->close();
    }
}

void
Logger::writeLog(string log, LogLevel logLevel)
{
    bool isDebugLog = logLevel == DEBUG;
    checkLogRollover();

    if(!isDebugLog || (isDebugLog && isDebugMode))
        getLogFile() << log << "\n";
}


