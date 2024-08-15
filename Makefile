# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -fPIC

# Shared library name
LIBRARY = liblogger.so

# Targets and dependencies
TARGET = sampleRunner
LIB_OBJS = logger.o
OBJS = circularbuffer.o sampleRunner.o

# Default rule to build the project
all: $(TARGET)

# Rule to build the shared library
$(LIBRARY): $(LIB_OBJS)
	$(CXX) -shared -o $(LIBRARY) $(LIB_OBJS)

# Rule to link the final executable with the shared library
$(TARGET): $(OBJS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -L. -llogger

# Rule to build circularbuffer.o
circularbuffer.o: circularbuffer.cpp circularbuffer.h logger.h
	$(CXX) $(CXXFLAGS) -c circularbuffer.cpp

# Rule to build sampleRunner.o
sampleRunner.o: sampleRunner.cpp circularbuffer.h
	$(CXX) $(CXXFLAGS) -c sampleRunner.cpp

# Rule to build logger.o
logger.o: logger.cpp logger.h
	$(CXX) $(CXXFLAGS) -c logger.cpp

# Clean rule to remove all built files
clean:
	rm -f $(OBJS) $(LIB_OBJS) $(TARGET) $(LIBRARY)

# Run rule to execute the compiled program
run: $(TARGET)
	LD_LIBRARY_PATH=. ./$(TARGET)

