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

# Detect OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	RM = rm -f
else
	RM = del /Q
endif

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o files
main.o:
	@mkdir -p $(dir main.o)
	$(CXX) $(CXXFLAGS) -I$(TCONTROLLER_DIR) -I$(EXCEPTIONS_DIR) -I$(HASHMAP_DIR) -c main.cpp -o main.o

tcontroller/tcontroller.o:
	@mkdir -p $(dir tcontroller/tcontroller.o)
	$(CXX) $(CXXFLAGS) -I$(TCONTROLLER_DIR) -I$(EXCEPTIONS_DIR) -I$(HASHMAP_DIR) -c tcontroller/tcontroller.cpp -o tcontroller/tcontroller.o

tcontroller/dynamic_tcontroller.o:
	@mkdir -p $(dir tcontroller/dynamic_tcontroller.o)
	$(CXX) $(CXXFLAGS) -I$(TCONTROLLER_DIR) -I$(EXCEPTIONS_DIR) -I$(HASHMAP_DIR) -c tcontroller/dynamic_tcontroller.cpp -o tcontroller/dynamic_tcontroller.o

tcontroller/static_tcontroller.o:
	@mkdir -p $(dir tcontroller/static_tcontroller.o)
	$(CXX) $(CXXFLAGS) -I$(TCONTROLLER_DIR) -I$(EXCEPTIONS_DIR) -I$(HASHMAP_DIR) -c tcontroller/static_tcontroller.cpp -o tcontroller/static_tcontroller.o

tcontroller/exceptions/exceptions.o:
	@mkdir -p $(dir tcontroller/exceptions/exceptions.o)
	$(CXX) $(CXXFLAGS) -I$(TCONTROLLER_DIR) -I$(EXCEPTIONS_DIR) -I$(HASHMAP_DIR) -c tcontroller/exceptions/exceptions.cpp -o tcontroller/exceptions/exceptions.o

tcontroller/hashmap/hashmap.o:
	@mkdir -p $(dir tcontroller/hashmap/hashmap.o)
	$(CXX) $(CXXFLAGS) -I$(TCONTROLLER_DIR) -I$(EXCEPTIONS_DIR) -I$(HASHMAP_DIR) -c tcontroller/hashmap/hashmap.cpp -o tcontroller/hashmap/hashmap.o

# Clean up build files
clean:
	$(RM) $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
