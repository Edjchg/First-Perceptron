#ifndef PERCETRON_HPP
#define PERCETRON_HPP

#include <memory>
#include <vector>

#include "MathOps.hpp"
#include "PerceptronTelemetry.hpp"

constexpr float PERCEPTRON_ETA_MIN_VALUE = 0.0f;
constexpr float PERCEPTRON_ETA_MAX_VALUE = 1.0f;
constexpr int PERCEPTRON_N_ITERATIONS_INITIAL_VALUE = 0;

/**
 * @brief Class representing a single-layer perceptron
 *
 * This class implements a single-layer perceptron that can be trained
 * to classify data into two classes. It uses a simple learning rule
 * based on the perceptron learning algorithm. The perceptron can be
 * trained with a set of inputs and expected outputs, and it can make
 * predictions based on the learned weights. The class also includes
 * telemetry functionality to collect error values and weights for each epoch.
 * The perceptron can be configured with a learning rate (eta) and the
 * number of iterations for training. The weights are initialized to zero
 * and updated during training based on the predictions and expected outputs.
 * The class provides methods to get and set the learning rate, number of iterations,
 * and weights. It also provides methods to predict the output for a given input
 * and to train the perceptron with a set of inputs and expected outputs.
 */
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

        /**
         * @brief Given a series of inputs the perceptron predicts if the
         *        data corresponds to the token it was trained for.
         *
         * @param float_vector[in] inputs of the individual to predict
         *
         * @return float 1 if the prediction is positive, -1 otherwise.
         */
        float predict(std::vector<float> inputXs) const;

       /**
        * @brief Given a series of inputs and expected results this
        *        function will perform the weight update based on the
        *        results of the predictions over the inputs and over
        *        the epochs.
        *
        * @param[in] inputXs
        *
        * @param[in] expectedYs
        *
        */
        void trainPerceptron(std::vector<std::vector<float>> inputXs, 
                             std::vector<int> expectedYs);

    private:
        float _eta;
        int _n_iterations;
        std::vector<float> _weights;
        std::vector<float> _errors;

        std::unique_ptr<MathOps> _mathOps;
        std::unique_ptr<PerceptronTelemetry> _telemetry;

        /**
         * @brief Given a series of inputs this function will calculate
         *        the weighted sum of the inputs and the weights.
         *
         * @param inputXs vector of inputs to calculate the weighted sum
         * @return float the weighted sum of the inputs and weights
         */
        float weightedSum(std::vector<float> inputXs) const;

        /**
         * @brief This function will update the weights of the perceptron
         *        based on the update value and the inputs.
         * @param updateValue the value to update the weights with
         * @param iInputX vector of inputs to update the weights with
         */
        void updateWeights(float updateValue, std::vector<float> iInputX);
};

#endif /* PERCETRON_HPP */
