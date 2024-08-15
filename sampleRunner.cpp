#include "circularbuffer.h"
using namespace std;

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
