
#ifndef CSVREADER_H
#define CSVREADER_H
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Class for reading and processing CSV files
 *
 * This class provides methods for reading a CSV file, extracting data,
 * shuffling it, and saving processed data back to a CSV file. It is
 * designed to work with datasets used for training machine learning
 * models, such as perceptrons.
 */
class CSVReader {
    public:
        CSVReader();
        ~CSVReader();

        // -- Setters & Getters --
        void setLabelColumn(int labelColumn);
        std::vector<std::vector<float>> getXValues(void) const; // Features
        std::vector<int> getYValues(void) const; // Labels
        std::vector<std::string> getUniqueLabels(void) const;
        void setTrainingPercentage(float percentage);
        std::vector<std::vector<float>> getXValuesTraining(void) const;
        std::vector<std::vector<float>> getXValuesTesting(void) const;
        std::vector<int> getYValuesTraining(void) const;
        std::vector<int> getYValuesTesting(void) const;
        std::vector<int> getOriginalYVals(void) const;
        std::vector<int> getOriginalYTrainingVals(void) const;
        std::vector<int> getOriginalYTestingVals(void) const;
        void setSaveDataFileName(std::string name);
        // -- End Setters & Getters --

        /**
         * @brief This function opens the CVS file to read the dataset
         *
         * @param[in] string The string describing the path where the file
         *                   is located at.
         */
        void openFile(std::string filePath);

        /**
         * @brief   This function parses the CVS file in order to convert it to
         *          vectors and matrixes according to the morphology of the data.
         * @details It will separate the data with "," delimiter, so ensure the
         *          input file delimiters are "," between columns.
         */
        void dataExtractor(void);

        /**
         * @brief This function shuffles the already parsed data in order to
         *        add variance to the training/testing data.
         */
        void shuffleData(void);

        /**
         * @brief   This function changes the labels into -1 or 1 depending
         *          on the token, if the label is equal to the token then
         *          the original label will be replaced to 1, -1 otherwise.
         *
         * @details The perceptron only can train with a data set that is
         *          classified between the data corresponding to the token
         *          and the data that does not correspond to the token.
         */
        void filterYLabelsPerToken(std::string token);

        /**
         * @brief This function saves all the shuffled and processed data into
         *        a CVS file.
         */
        void saveDataToFile(void);

        /**
         * @brief This function read the Weights from a CVS file, parses them
         *        and convert them to a vector.
         *
         * @param[in] fileName the file path where the weights are.
         *
         * @return float vector of the processed weights
         */
        std::vector<float> readWeightsFromFile(std::string fileName);



    private:
        std::fstream _csvFile;
        int _labelColumn;
        std::string _filePath;
        int _rowsNumber;
        int _colsNumber;
        std::string saveDataFileName;

        std::vector<std::vector<float>> _xValues;
        std::vector<int> _yValues;
        std::vector<int> _yOriginalValues;

        std::vector<std::vector<float>> _xValuesTraining;
        std::vector<std::vector<float>> _xValuesTesting;

        std::vector<int> _yValuesTraining;
        std::vector<int> _yValuesTesting;
        std::vector<int> _yOriginalValuesTraining;
        std::vector<int> _yOriginalValuesTesting;

        /*
         * There is a need to store all the labels in
         * one list, without repeated values. While the
         * reader is reading the file, it needs to store
         * any new lable found, but at the same time,
         * assign a float key, so that key could be
         * assigned to yValues. 
         */
        std::vector<std::string> _uniqueLabels;

        /**
         * @brief This function appends a value to _uniqueLabels but before
         *        adding it, checks that the value is not already added,
         *        ensuring the values inside the vector are not repeated.
         *
         * @param[in] value value string that is requested to be added to.
         */
        void uniqueValueAppend(std::string value);

        /**
         * @brief This function extracts the index of a certain value in the vector
         *        to be consulted.
         *
         * @param[in] vectorToAsk the vector that will be consulted for the index of
         *            of the value.
         *
         * @param[in] value The value to be consulted in the vector.
         *
         * @return int of the index of the value consulted.
         */
        int getIndexOfValue(std::vector<std::string> vectorToAsk, std::string value);

        /**
         * @brief This function catches any error ocurred during the convertion process
         *        of a string to float.
         *
         * @param[in] numberToConvert the string containing the number to be converted.
         *
         * @return the value of the converted string to float.
         */
        float safeStringToFloat(std::string numberToConvert);
};

#endif /* CSVREADER_H */
