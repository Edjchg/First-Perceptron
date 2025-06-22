#include <random>
#include "CSVReader.hpp"

using namespace std;

CSVReader::CSVReader() {}
CSVReader::~CSVReader(){}

void CSVReader::setLabelColumn(int labelColumn) {
    this->_labelColumn = labelColumn;
}

vector<vector<float>> CSVReader::getXValues(void) const {
    return this->_xValues;
}

vector<int> CSVReader::getYValues(void) const {
    return this->_yValues;
}

vector<string> CSVReader::getUniqueLabels(void) const {
    return this->_uniqueLabels;
}

void CSVReader::setTrainingPercentage(float percentage) {
    int lenData = this->_xValues.size();

    int trainingPercentage = (int)(lenData * (percentage * 0.01));

    // Spliting the X Values:

    // Getting the iterators from X values:
    auto startingTrainingXVals = this->_xValues.begin();
    auto endingTrainingXVals = this->_xValues.begin() + trainingPercentage;

    auto startingTestingXVals = this->_xValues.begin() + trainingPercentage + 1;
    auto endingTestingXVals = this->_xValues.end();

    copy(startingTrainingXVals, endingTrainingXVals, back_inserter(this->_xValuesTraining));
    copy(startingTestingXVals, endingTestingXVals, back_inserter(this->_xValuesTesting));


    // Splitting the Y Values:

    // Getting the iterators from Y Values:
    auto startingTrainingYVals = this->_yValues.begin();
    auto endingTrainingYVals = this->_yValues.begin() + trainingPercentage;

    auto startingTestingYVals = this->_yValues.begin() + trainingPercentage + 1;
    auto endingTestingYVals = this->_yValues.end();

    copy(startingTrainingYVals, endingTrainingYVals, back_inserter(this->_yValuesTraining));
    copy(startingTestingYVals, endingTestingYVals, back_inserter(this->_yValuesTesting));

    auto startingTrainingOriginalYVals = this->_yOriginalValues.begin();
    auto endingTrainingOriginalYVals = this->_yOriginalValues.begin() + trainingPercentage;

    auto startingTestingOriginalYVals = this->_yOriginalValues.begin() + trainingPercentage + 1;
    auto endingTestingOriginalYVals = this->_yOriginalValues.end();

    copy(startingTrainingOriginalYVals, endingTrainingOriginalYVals, back_inserter(this->_yOriginalValuesTraining));
    copy(startingTestingOriginalYVals, endingTestingOriginalYVals, back_inserter(this->_yOriginalValuesTesting));

}

vector<vector<float>> CSVReader::getXValuesTraining(void) const {
    return this->_xValuesTraining;
}
vector<vector<float>> CSVReader::getXValuesTesting(void) const {
    return this->_xValuesTesting;
}
vector<int> CSVReader::getYValuesTraining(void) const {
    return this->_yValuesTraining;
}
vector<int> CSVReader::getYValuesTesting(void) const {
    return this->_yValuesTesting;
}

vector<int> CSVReader::getOriginalYVals(void) const {
    return this->_yOriginalValues;
}

vector<int> CSVReader::getOriginalYTrainingVals(void) const {
    return this->_yOriginalValuesTraining;
}
vector<int> CSVReader::getOriginalYTestingVals(void) const {
    return this->_yOriginalValuesTesting;
}

void CSVReader::setSaveDataFileName(string name) {
    this->saveDataFileName = name;
}

void CSVReader::openFile(string filePath){
    this->_csvFile.open(filePath, ios::in);
    if (!this->_csvFile.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }
}

void CSVReader::dataExtractor(void) {

    string tempRow, line, datum, delimiter = ",";
    int delimiterLen = delimiter.length();
    vector<float> row;

    while (this->_csvFile >> tempRow) {

        int columnCounter = 0;
        
        /*
         * Read the line with data of the form:
         *  - datum1,datum2,...,datumN
         *  - datum1,datum2,...,datumN
         */

        /*
         * Creating a copy of line to split
         * it out in further steps:
         */
        string tempLine(tempRow);

        /*
         * Cleaning the row vector, since it was used,
         * for previous lines:
         */
        row.clear();

        /*
         * Once we have the line, we want to split it
         * into the datums in between ","
         *
         * What getline does in this case is to go through
         * the line finding the delimiter "," and storing
         * the word in between them in the variable "datum"
         */
        size_t position = 0;
        while (tempLine.length() > 0) {

            position = tempLine.find(delimiter);
            
            if (position != string::npos){
               /*
                * The word will be in between the start position
                * of the string, until the "," delimiter, so I'm
                * getting the substring, and store that into the
                * variable word:
                */
                datum = tempLine.substr(0, position);
            } else {
                datum = tempLine;
            }

            if (columnCounter == this->_labelColumn) {
                /*
                 * For every found label, the algorithm is storing it
                 * to a vector with unique value appender wrapper,
                 * this allows two important facts:
                 * - Does not store duplicated values
                 * - Does store the values in the order they arrived.
                 */
                this->uniqueValueAppend(datum);

                /*
                 * Storing just the index of the uniqueLable in the
                 * corresponding unordered set, to the y values:
                 */
                int correspondingLabelIndex = this->getIndexOfValue(this->_uniqueLabels, datum);

                this->_yValues.push_back(correspondingLabelIndex);

            } else {
                /*
                 * Assuming the value is a floatant number, then we need to
                 * convert it from string to float.
                 */
                float convertedDatum = this->safeStringToFloat(datum);

                /*
                 * Storing the new converted value to the row:
                 */
                row.push_back(convertedDatum);
            }

            /*
             * Once we read the first datum, then deleting it,
             * so the next datum to read will be in the first
             * position:
             */
            if (position != string::npos){

                tempLine.erase(0, position + delimiterLen);
            } else {
                tempLine.clear();
            }
            columnCounter++;
            
        }

        /*
         * Once reached this point, means we finished reading a single line,
         * but before continue with the next one, then we need to store the
         * entire row into the xValues vector:
         */
        this->_xValues.push_back(row);
    }
    this->_csvFile.close();
}

void CSVReader::uniqueValueAppend(string value) {
    auto resultantIterator = find(this->_uniqueLabels.begin(), this->_uniqueLabels.end(), value);

    // Checking if the element is not present in the vector:
    if (resultantIterator == this->_uniqueLabels.end()) {
        // If the value is not present then append it:
        this->_uniqueLabels.push_back(value);
    }
    // If it is present then do not add it.
}

int CSVReader::getIndexOfValue(vector<string> vectorToAsk, string value) {
    auto resultantIterator = find(vectorToAsk.begin(), vectorToAsk.end(), value);

    if (resultantIterator != vectorToAsk.end()) {
        return distance(vectorToAsk.begin(), resultantIterator);
    }
    // Reaching this point means that the value was not found in the vector.
    return -1;
}

float CSVReader::safeStringToFloat(string numberToConvert) {
    float convertedNumber = 0.0f;
    try {
        convertedNumber = stof(numberToConvert);
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        convertedNumber = 0.0f;
    } catch (const out_of_range& e) {
        cerr << "Out of range: " << e.what() << endl;
        convertedNumber = 0.0f;
    } catch (...) {
        cerr << "An unexpected error occurred while converting string to float." << endl;
        convertedNumber = 0.0f;
    }
    return convertedNumber;
}

void CSVReader::shuffleData(void) {

    int lenData = this->_xValues.size();

    int minRandVal = 0;
    int maxRandVal = lenData - 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minRandVal, maxRandVal);



    for (int index = 0; index < lenData; index++) {
        int randomValue = distrib(gen);
        
        // Get the current data and lable:
        auto currentXVal = this->_xValues.at(index);
        auto currentYVal = this->_yValues.at(index);
        

        // Get the random value data and lable:
        auto randomXVal = this->_xValues.at(randomValue);
        auto randomYVal = this->_yValues.at(randomValue);
        

        // Swapp values:
        this->_xValues.at(index) = randomXVal;
        this->_xValues.at(randomValue) = currentXVal;


        this->_yValues.at(index) = randomYVal;
        this->_yValues.at(randomValue) = currentYVal;

        if (this->_yOriginalValues.size() > 0) {
            auto currentOriginalYVal = this->_yOriginalValues.at(index);
            auto randomOriginalYVal = this->_yOriginalValues.at(randomValue);
            this->_yOriginalValues.at(index) = randomOriginalYVal;
            this->_yOriginalValues.at(randomValue) = currentOriginalYVal;
        }
    }
}

void CSVReader::filterYLabelsPerToken(string token) {
    int labelsLen = this->_yValues.size();

    copy(this->_yValues.begin(), this->_yValues.end(), back_inserter(this->_yOriginalValues));

    /*
     * Convert token to int index, to do that, need to ask
     * the unique labels the position of that token:
     */
    int tokenIndex = this->getIndexOfValue(this->_uniqueLabels, token);

    /*
     * Iterate over the yValues and place a 1 to ones that match the token
     * and place a -1 to ones that not:
     */
    
    for (int index = 0; index < labelsLen; index++) {
        this->_yValues.at(index) = this->_yValues.at(index) == tokenIndex ? 1 : -1;
    }
}

void CSVReader::saveDataToFile(void) {
    ofstream outputFile;
    outputFile.open(this->saveDataFileName);
    if (!outputFile.is_open()) {
        cerr << "Error opening file: " << this->saveDataFileName << endl;
        return;
    }

    int lenData = this->_xValues.size();

    for (int dataIndex = 0; dataIndex < lenData; dataIndex++) {

        for (auto xVal : this->_xValues.at(dataIndex)) {
            outputFile << xVal << " ";
        }

        outputFile << "|" << this->_yValues.at(dataIndex) << " | " << this->_yOriginalValues.at(dataIndex) << " " << this->_uniqueLabels.at(this->_yOriginalValues.at(dataIndex)) << endl;
    }

    outputFile.close();
}

vector<float> CSVReader::readWeightsFromFile(string fileName) {
    fstream inputFile;
    inputFile.open(fileName, ios::in);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return vector<float>();
    }

    string tempRow, line, datum, delimiter = ",";
    int delimiterLen = delimiter.length();
    vector<float> row;

    while (inputFile >> tempRow) {

        string tempLine(tempRow);
        size_t position = 0;

        while (tempLine.length() > 0) {

            position = tempLine.find(delimiter);

            if (position != string::npos){
               /*
                * The word will be in between the start position
                * of the string, until the "," delimiter, so I'm
                * getting the substring, and store that into the
                * variable word:
                */
                datum = tempLine.substr(0, position);
            } else {
                datum = tempLine;
            }

            /*
             * Assuming the value is a floatant number, then we need to
             * convert it from string to float.
             */
            float convertedDatum = this->safeStringToFloat(datum);

            /*
             * Storing the new converted value to the row:
             */
            row.push_back(convertedDatum);

            /*
             * Once we read the first datum, then deleting it,
             * so the next datum to read will be in the first
             * position:
             */
            if (position != string::npos){
                tempLine.erase(0, position + delimiterLen);
            } else {
                tempLine.clear();
            }
        }
    }
    inputFile.close();
    return row;
}
