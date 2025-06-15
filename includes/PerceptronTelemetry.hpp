#ifndef PERCEPTRON_TELEMETRY_H
#define PERCEPTRON_TELEMETRY_H

#include <vector>
#include <string>

class PerceptronTelemetry {
    public:
        PerceptronTelemetry();
        ~PerceptronTelemetry();

        void setName(std::string perceptronName);
        void collectErrors(float error);
        void collectWeightsPerEpoch(std::vector<float> currentEpochWeights);
        void saveDataToFile(void);

    private:
        std::string _perceptronName;
        std::vector<float> _errors;
        std::vector<std::vector<float>> _weightsPerEpoch;
};

#endif /* PERCEPTRON_TELEMETRY_H */