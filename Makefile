CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

SRCS = iris_dataset_experiment.cpp sources/Perceptron.cpp sources/MathOps.cpp sources/CSVReader.cpp
SRCS_B = bird_detection_experiment.cpp sources/Perceptron.cpp sources/MathOps.cpp sources/CSVReader.cpp sources/PerceptronTelemetry.cpp
HDRS := -Iincludes # This allows me to include the headers as #include "Perceptron.hpp" and not
                   # #include "../includes/Perceptron.hpp"
OBJS = $(SRCS:.cpp=.o)
TARGET = neural_iris_dataset
TARGET_B = neural_bird_dataset

neural_iris_dataset:
	SRCS += iris_dataset_experiment.cpp
	$(CXX) $(CXXFLAGS) $(HDRS) -o $(TARGET) $(SRCS)

run_neural_iris_dataset:
	./$(TARGET)

neural_bird_dataset:
	$(CXX) $(CXXFLAGS) $(HDRS) -o $(TARGET_B) $(SRCS_B)

run_neural_bird_dataset:
	./$(TARGET_B)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET_B)
