//#include <ostream>
#include <fstream>

#include "PerceptronTelemetry.hpp"

using namespace std;

PerceptronTelemetry::PerceptronTelemetry() {}

PerceptronTelemetry::~PerceptronTelemetry(){}

void PerceptronTelemetry::setName(std::string perceptronName) {
    this->_perceptronName = perceptronName;
}

void PerceptronTelemetry::collectErrors(float error) {
    this->_errors.push_back(error);
}
void PerceptronTelemetry::collectWeightsPerEpoch(std::vector<float> currentEpochWeights) {
    this->_weightsPerEpoch.push_back(currentEpochWeights);
}

void PerceptronTelemetry::saveDataToFile(void) {
    size_t perceptronNameLen = this->_perceptronName.length();
    if (perceptronNameLen == 0) {
        return;
    }

    string fileNameExtension(".csv");

    string allWeightsFileName = this->_perceptronName + "_AllWeights" + fileNameExtension;

    string fittestsWeightsFileName = this->_perceptronName + "_FittestWeights" + fileNameExtension;

    string errorsFileName = this->_perceptronName + "_Errors" + fileNameExtension;

    ofstream OFAllWeights, OFFittestWeights, OFErrors;

    OFAllWeights.open(allWeightsFileName);
    for (auto weightVector : this->_weightsPerEpoch) {
        for (auto weight : weightVector) {
            OFAllWeights << weight << ",";
        }
        OFAllWeights << endl;
    }
    OFAllWeights.close();


    OFFittestWeights.open(fittestsWeightsFileName);
    auto fittestWeightVector = this->_weightsPerEpoch.back();
    for (auto fittestWeight : fittestWeightVector) {
        OFFittestWeights << fittestWeight << ",";
    }
    OFFittestWeights << endl;
    OFFittestWeights.close();


    OFErrors.open(errorsFileName);
    for (auto error : this->_errors) {
        OFErrors << error << ",";
    }
    OFErrors << endl;
    OFErrors.close();
}
