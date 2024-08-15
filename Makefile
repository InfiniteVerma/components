# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

# Targets and dependencies
TARGET = sampleRunner
OBJS = circularbuffer.o logger.o sampleRunner.o

# Default rule to build the project
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build circularbuffer.o
circularbuffer.o: circularbuffer.cpp circularbuffer.h logger.h
	$(CXX) $(CXXFLAGS) -c circularbuffer.cpp

# Rule to build logger.o
logger.o: logger.cpp logger.h
	$(CXX) $(CXXFLAGS) -c logger.cpp

# Rule to build sampleRunner.o
sampleRunner.o: sampleRunner.cpp circularbuffer.h
	$(CXX) $(CXXFLAGS) -c sampleRunner.cpp

# Clean rule to remove all built files
clean:
	rm -f $(OBJS) $(TARGET)

# Run rule to execute the compiled program
run: $(TARGET)
	./$(TARGET)

