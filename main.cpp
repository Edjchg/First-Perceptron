#include <iostream>
#include "Perceptron.hpp"

#include "CSVReader.hpp"

using namespace std;

/**
 * Iris data set was downloaded from https://archive.ics.uci.edu/dataset/53/iris
 */

int main(void) {

    Perceptron perceptron;
    perceptron.setEta(0.1);
    perceptron.setNIterations(10);

    CSVReader reader;
    reader.openFile("iris_dataset/iris.csv");
    reader.setLableColumn(4);
    reader.dataExtractor();
    reader.filterYLabelsPerToken("Iris-setosa");
    reader.shuffleData();
    reader.saveDataToFile();
    reader.setTrainingPercentage(75);


    auto trainXData = reader.getXValuesTraining();
    auto trainLables = reader.getYValuesTraining();

    perceptron.trainPerceptron(trainXData, trainLables);

    auto testXData = reader.getXValuesTesting();
    auto testYData = reader.getYValuesTesting();
    auto uniqueLables = reader.getUniqueLables();
    auto originalYLabels = reader.getoriginalYTestingVals();

    cout << "Size of test data: " << testXData.size() << endl;

    int index = 0;
    for (auto xVal : testXData) {
        cout << "Consulted plant " << index << " was " << uniqueLables.at(originalYLabels.at(index)) << " Is this plant Iris-setosa ? Perceptron answer: " << (perceptron.predict(xVal) == 1 ? "yes" : "no") << endl;
        index++;
    }

    return 0;
}