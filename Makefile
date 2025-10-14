CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = ra2_main

SRCS = ra2_main.cpp core/text_loader.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) results.csv

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
