CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

SRCS = main.cpp sources/Perceptron.cpp sources/MathOps.cpp sources/CSVReader.cpp
HDRS := -Iincludes # This allows me to include the headers as #include "Perceptron.hpp" and not
                   # #include "../includes/Perceptron.hpp"
OBJS = $(SRCS:.cpp=.o)
TARGET = neural_network

neural:
	$(CXX) $(CXXFLAGS) $(HDRS) -o $(TARGET) $(SRCS)

run:
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
