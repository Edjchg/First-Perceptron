#ifndef PERCEPTRON_TELEMETRY_H
#define PERCEPTRON_TELEMETRY_H

#include <vector>
#include <string>

/**
 * @brief Class for collecting telemetry data from the perceptron
 *
 * This class is responsible for collecting error values and weights
 * for each epoch during the training of a perceptron. It allows setting
 * the name of the perceptron and saving the collected data to a file.
 * The telemetry data can be used for analysis and debugging purposes.
 */
class PerceptronTelemetry {
    public:
        PerceptronTelemetry();
        ~PerceptronTelemetry();

        /**
         * @brief Set the name of the perceptron
         *
         * @param perceptronName the name to set
         */
        void setName(std::string perceptronName);

        /**
         * @brief Collect an error value for telemetry
         *
         * @param error the error value to collect
         */
        void collectErrors(float error);

        /**
         * @brief Collect the weights for the current epoch
         *
         * @param currentEpochWeights the weights to collect
         */
        void collectWeightsPerEpoch(std::vector<float> currentEpochWeights);

        /**
         * @brief Save the telemetry data to a file
         *
         */
        void saveDataToFile(void);

    private:
        std::string _perceptronName;
        std::vector<float> _errors;
        std::vector<std::vector<float>> _weightsPerEpoch;
};

#endif /* PERCEPTRON_TELEMETRY_H */
