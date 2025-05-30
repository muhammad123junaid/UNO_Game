CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

TARGET = uno

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o uno.exe
