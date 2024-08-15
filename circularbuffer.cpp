#include "circularbuffer.h"

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

    logger = new Logger("circularBuffer");
}

CircularBuffer::~CircularBuffer()
{
    delete []array;
    delete logger;
}

void
CircularBuffer::writeData(int data)
{
    lock_guard<std::mutex> lock(bufMutex);
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
    lock_guard<std::mutex> lock(bufMutex);
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
