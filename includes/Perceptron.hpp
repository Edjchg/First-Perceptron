#ifndef PERCETRON_HPP
#define PERCETRON_HPP

#include <memory>
#include <vector>

#include "MathOps.hpp"
#include "PerceptronTelemetry.hpp"

constexpr float PERCEPTRON_ETA_MIN_VALUE = 0.0f;
constexpr float PERCEPTRON_ETA_MAX_VALUE = 1.0f;
constexpr int PERCEPTRON_N_ITERATIONS_INITIAL_VALUE = 0;

class Perceptron {
    public:
        // Constructor
        Perceptron(std::string perceptronName);
        // Destructor
        ~Perceptron();

        // -- Getters and Setters --
        float getEta(void) const;
        void setEta(float eta);
        int getNIterations(void) const;
        void setNIterations(int n_iterations);
        std::vector<float> getWeights(void) const;
        void setWeights(const std::vector<float>& weights);
        // -- End Getters and Setters --

        float weightedSum(std::vector<float> inputXs) const;

        float predict(std::vector<float> inputXs) const;

        void updateWeights(float updateValue, std::vector<float> iInputX);

        void trainPerceptron(std::vector<std::vector<float>> inputXs, 
                             std::vector<int> expectedYs);

    private:
        float _eta;
        int _n_iterations;
        std::vector<float> _weights;
        std::vector<float> _errors;

        std::unique_ptr<MathOps> _mathOps;
        std::unique_ptr<PerceptronTelemetry> _telemetry;
};



#endif
