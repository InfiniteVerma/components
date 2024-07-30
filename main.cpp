#include <cassert>
#include <iostream>
#include <sys/types.h>
using namespace std;

class CircularBuffer {
    private:
        ssize_t size;
        int* array;
    public:
        CircularBuffer(ssize_t);
        CircularBuffer() = delete;
        ~CircularBuffer();

        int getSize();

        void write(int data);
};

CircularBuffer::CircularBuffer(ssize_t s)
{
    if(s > 50)
    {
        cout << "ERROR: Max allowed size is 50";
        assert(0);
    }
    size = s;
    array = new int[s];
}

CircularBuffer::~CircularBuffer()
{
    delete []array;
}

int
CircularBuffer::getSize()
{
    return size;
}

int main() {
    CircularBuffer buffer(20);
    cout << " buffer size: " << buffer.getSize() << "\n";
    return 0;
}
