# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Directories
SRC_DIR = .
TCONTROLLER_DIR = $(SRC_DIR)/tcontroller
EXCEPTIONS_DIR = $(TCONTROLLER_DIR)/exceptions
HASHMAP_DIR = $(TCONTROLLER_DIR)/hashmap

# Source files
SRCS = main.cpp \
       tcontroller/tcontroller.cpp \
       tcontroller/dynamic_tcontroller.cpp \
       tcontroller/static_tcontroller.cpp \
       tcontroller/exceptions/exceptions.cpp \
       tcontroller/hashmap/hashmap.cpp

# Object files
OBJS = main.o \
       tcontroller/tcontroller.o \
       tcontroller/dynamic_tcontroller.o \
       tcontroller/static_tcontroller.o \
       tcontroller/exceptions/exceptions.o \
       tcontroller/hashmap/hashmap.o

# Executable
TARGET = a.out

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o a.out main.o tcontroller/tcontroller.o tcontroller/dynamic_tcontroller.o tcontroller/static_tcontroller.o tcontroller/exceptions/exceptions.o tcontroller/hashmap/hashmap.o

# Compile .cpp files into .o files
main.o: main.cpp
    $(CXX) $(CXXFLAGS) -c main.cpp -o main.o

tcontroller/tcontroller.o: tcontroller/tcontroller.cpp
    $(CXX) $(CXXFLAGS) -c tcontroller/tcontroller.cpp -o tcontroller/tcontroller.o

tcontroller/dynamic_tcontroller.o: tcontroller/dynamic_tcontroller.cpp
    $(CXX) $(CXXFLAGS) -c tcontroller/dynamic_tcontroller.cpp -o tcontroller/dynamic_tcontroller.o

tcontroller/static_tcontroller.o: tcontroller/static_tcontroller.cpp
    $(CXX) $(CXXFLAGS) -c tcontroller/static_tcontroller.cpp -o tcontroller/static_tcontroller.o

tcontroller/exceptions/exceptions.o: tcontroller/exceptions/exceptions.cpp
    $(CXX) $(CXXFLAGS) -c tcontroller/exceptions/exceptions.cpp -o tcontroller/exceptions/exceptions.o

tcontroller/hashmap/hashmap.o: tcontroller/hashmap/hashmap.cpp
    $(CXX) $(CXXFLAGS) -c tcontroller/hashmap/hashmap.cpp -o tcontroller/hashmap/hashmap.o

# Clean up build files
clean:
    rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
    ./$(TARGET)

# Phony targets
.PHONY: all clean run