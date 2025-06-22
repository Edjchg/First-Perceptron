/*
 * Audio data sets: https://huggingface.co/blog/audio-datasets
 *
 * These are the birds audio datasets: https://huggingface.co/datasets?task_categories=task_categories:audio-classification&sort=downloads&search=bir
 *
 * BirdSet https://huggingface.co/datasets/DBD-research-group/BirdSet
 *
 * Selecting the NES  
 * Colombia-Costa Rica Birds data set:
 * Downloading the data set from: https://zenodo.org/records/7525349

 * Annotating which species could be used for perceptron training:
 *
 * Colombia S01:
 * ccbfin
 * whtdov
 *
 * Costa Rica S02:
 * wegspa1
 */
#include <iostream>
#include "Perceptron.hpp"

#include "CSVReader.hpp"

using namespace std;

static void perceptronTrainAndUse(void) {
    /*Features:
     * Location,Start Time (s),End Time (s),Low Freq (Hz),High Freq (Hz),Common Name
     */
    Perceptron perceptron("bird_detector");
    perceptron.setEta(0.9);
    perceptron.setNIterations(2);

    CSVReader reader;
    reader.openFile("nes_birdset_dataset/subset_three_species.csv");
    reader.setLableColumn(5);
    reader.dataExtractor();
    reader.filterYLabelsPerToken("White-eared-Ground-Sparrow"); // wegspa1
    reader.shuffleData();
    reader.setSaveDataFileName("nes_birdset_dataset/result.csv");
    reader.saveDataToFile();
    reader.setTrainingPercentage(75);


    auto trainXData = reader.getXValuesTraining();
    auto trainLables = reader.getYValuesTraining();

    perceptron.trainPerceptron(trainXData, trainLables);

    auto testXData = reader.getXValuesTesting();
    auto testYData = reader.getYValuesTesting();
    auto uniqueLables = reader.getUniqueLables();
    auto originalYLabels = reader.getoriginalYTestingVals();

    /*cout << "Size of test data: " << testXData.size() << endl;

    int index = 0;
    for (auto xVal : testXData) {
        cout << "Consulted bird " << index << " was " << uniqueLables.at(originalYLabels.at(index)) << " Is this bird Chestnut-capped Brushfinch ? Perceptron answer: " << (perceptron.predict(xVal) == 1 ? "yes" : "no") << endl;
        index++;
    }*/
}

static void usePerceptronTrained(void) {

    CSVReader reader;
    reader.openFile("nes_birdset_dataset/subset_three_species.csv");
    reader.setLableColumn(5);
    reader.dataExtractor();
    reader.filterYLabelsPerToken("White-eared-Ground-Sparrow");
    reader.shuffleData();
    reader.setSaveDataFileName("nes_birdset_dataset/result.csv");
    reader.saveDataToFile();
    reader.setTrainingPercentage(75);


    auto testXData = reader.getXValuesTesting();
    auto testYData = reader.getYValuesTesting();
    auto uniqueLables = reader.getUniqueLables();
    auto originalYLabels = reader.getoriginalYTestingVals();

    auto alreadyTrainedWeights = reader.readWeightsFromFile("bird_detector_FittestWeights.csv");
    /*
     * Need to Load the weights to the Perceptron, instead of train it:
     */
    Perceptron perceptron("bird_detector");
    perceptron.setWeights(alreadyTrainedWeights);
    
    int index = 0;
    for (auto xVal : testXData) {
        cout << "Consulted bird " << index << " was " << uniqueLables.at(originalYLabels.at(index)) << " Is this bird White-eared Ground-Sparrow ? Perceptron answer: " << (perceptron.predict(xVal) == 1 ? "yes" : "no") << endl;
        index++;
    }
}

int main() {
    perceptronTrainAndUse();

    usePerceptronTrained();
}