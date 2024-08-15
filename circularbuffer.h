#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <memory>
#include "logger.h"

class CircularBuffer {
    private:
        ssize_t size;
        int* array;
        int writePtr;
        int readPtr;
        Logger* logger;
        mutex bufMutex;

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
