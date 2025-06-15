
#ifndef CSVREADER_H
#define CSVREADER_H
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CSVReader {
    public:
        CSVReader();
        ~CSVReader();

        // -- Setters & Getters --
        void setLableColumn(int lableColumn);
        std::vector<std::vector<float>> getXValues(void);
        std::vector<int> getYValues(void); // Lables
        std::vector<std::string> getUniqueLables(void);
        void setTrainingPercentage(float percentage);
        std::vector<std::vector<float>> getXValuesTraining(void);
        std::vector<std::vector<float>> getXValuesTesting(void);
        std::vector<int> getYValuesTraining(void);
        std::vector<int> getYValuesTesting(void);
        std::vector<int> getOriginalYVals(void);
        std::vector<int> getOriginalYTrainingVals(void);
        std::vector<int> getoriginalYTestingVals(void);
        void setSaveDataFileName(std::string name);
        // -- End Setters & Getters --
        void openFile(std::string filePath);
        void dataExtractor(void);
        void shuffleData(void);
        void filterYLabelsPerToken(std::string token);
        void saveDataToFile(void);
        std::vector<float> readWeightsFromFile(std::string fileName);



    private:
        std::fstream _csvFile;
        int _lableColumn;
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
         * There is a need to store all the lables in
         * one list, without repeated values. While the
         * reader is reading the file, it needs to store
         * any new lable found, but at the same time,
         * assign a float key, so that key could be
         * assigned to yValues. 
         */
        //std::unordered_set<std::string> uniqueLables;
        std::vector<std::string> _uniqueLables;

        void uniqueValueAppend(std::string value);

        int getIndexOfValue(std::vector<std::string> vectorToAsk, std::string value);

        float safeStringToFloat(std::string numberToConvert);
};

#endif /* CSVREADER_H */