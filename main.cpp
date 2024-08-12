#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
using namespace std;

#define LOG_FILE_NAME "circularBuffer001.log"

enum LogLevel {
    INFO = 1,
    DEBUG = 2,
};

class Logger {
    private:
        ofstream logPtr;
        bool isDebugMode;
    public:
        Logger();
        ~Logger();

        void writeLog(string log, LogLevel logLevel = INFO);
};

Logger::Logger()
{
    logPtr = ofstream(LOG_FILE_NAME);

    char* level = getenv("LOGLEVEL");

    if(level)
    {
        if(strcmp(level, "DEBUG") == 0)
            isDebugMode = true;
        else
            isDebugMode = false;
    }

    if(!logPtr.is_open())
    {
        cout << "ERROR could not open log file\n";
        assert(1);
    }

    writeLog("Initialized log");
}

Logger::~Logger()
{
    if(logPtr.is_open())
    {
        logPtr.close();
    }
}

void
Logger::writeLog(string log, LogLevel logLevel)
{
    bool isDebugLog = logLevel == DEBUG;

    if(!isDebugLog || (isDebugLog && isDebugMode))
        logPtr << log << "\n";
}

class CircularBuffer {
    private:
        ssize_t size;
        int* array;
        int writePtr;
        int readPtr;
        Logger* logger;

    public:
        CircularBuffer(ssize_t);
        CircularBuffer() = delete;
        ~CircularBuffer();

        void writeData(int data);
        int readData();

        void debugRead();

        int getSize();

        void write(int data);
};

CircularBuffer::CircularBuffer(ssize_t s)
{
    if(s > 50)
    {
        logger->writeLog("ERROR: Max allowed size is 50");
        assert(1);
    }
    size = s;
    array = new int[s];
    readPtr = 0;
    writePtr = 0;

    logger = new Logger();
}

CircularBuffer::~CircularBuffer()
{
    delete []array;
    delete logger;
}

void
CircularBuffer::writeData(int data)
{
    logger->writeLog("writeData BEGIN", DEBUG);
    if(writePtr >= size)
    {
        logger->writeLog("writePtr >= size, updating it", DEBUG);
        writePtr = writePtr % size;
    }

    logger->writeLog("writePtr: " + to_string(writePtr), DEBUG);

    array[writePtr++] = data;
    logger->writeLog("writeData END", DEBUG);
}

int
CircularBuffer::readData()
{
    logger->writeLog("readData BEGIN", DEBUG);
    if(readPtr >= size)
    {
        logger->writeLog("readPtr >= size, updating it", DEBUG);
        readPtr = readPtr % size;
    }

    logger->writeLog("readPtr: " + to_string(readPtr));

    logger->writeLog("readData END", DEBUG);

    int delEle = array[readPtr];
    array[readPtr] = 0;
    readPtr++;
    return delEle;
}

int
CircularBuffer::getSize()
{
    return size;
}

void
CircularBuffer::debugRead()
{
    logger->writeLog("debugRead BEGIN");

    logger->writeLog("size: " + to_string(size));
    logger->writeLog("readPtr: " + to_string(readPtr)); 
    logger->writeLog("writePtr: " + to_string(writePtr)); 

    logger->writeLog("Array: ");
    string tmp = "";
    for(int i=0;i<size;i++) {
        tmp += to_string(array[i]) + "\t";
    }
    logger->writeLog(tmp);

    logger->writeLog("debugRead END");
}

int main() {
    CircularBuffer buffer(5);

    buffer.writeData(1);
    buffer.writeData(2);
    buffer.writeData(3);
    buffer.writeData(4);
    buffer.writeData(5);

    buffer.debugRead();
    buffer.writeData(7);
    buffer.writeData(8);
    buffer.debugRead();

    return 0;
}
