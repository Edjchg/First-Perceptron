CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

SRCS = iris_dataset_experiment.cpp sources/Perceptron.cpp sources/MathOps.cpp sources/CSVReader.cpp
HDRS := -Iincludes # This allows me to include the headers as #include "Perceptron.hpp" and not
                   # #include "../includes/Perceptron.hpp"
OBJS = $(SRCS:.cpp=.o)
TARGET = neural_iris_dataset

neural_iris_dataset:
	$(CXX) $(CXXFLAGS) $(HDRS) -o $(TARGET) $(SRCS)

run_neural_iris_dataset:
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
