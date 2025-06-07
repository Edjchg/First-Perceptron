#include <iostream>

#include "MathOps.hpp"
#include "Perceptron.hpp"

using namespace std;

/**
 * Perceptron class implementation.
 *
 * A perceptron is a model of neural, and it is the simplest form of a neural network.
 * It consists of a single neuron that takes multiple inputs, applies weights to them,
 * sums them up, and passes the result through an activation function to produce an output.
 */

Perceptron::Perceptron() : _eta(PERCEPTRON_ETA_MIN_VALUE),
                           _n_iterations(PERCEPTRON_N_ITERATIONS_INITIAL_VALUE),
                           _mathOps(make_unique<MathOps>()) {
    // Constructor implementation:

}

Perceptron::~Perceptron() {
    // Destructor implementation:

    /*
     * Since _mathOps is a smart pointer of type
     * unique_ptr, it will automatically dealloacte
     * when the Perceptron object is destroyed.
     *
     * However, if you want to explicitly reset it,
     * you can do so by calling reset() on the
     * unique_ptr. This will release the memory
     * allocated for the MathOps object and set
     * the unique_ptr to nullptr.
     */
    if (this->_mathOps != nullptr) {
        this->_mathOps.reset();
    }

    this->_weights.clear();
}

float Perceptron::getEta() const{
    return this->_eta;
}

void Perceptron::setEta(float eta) {
    if (PERCEPTRON_ETA_MIN_VALUE <= eta &&
        eta <= PERCEPTRON_ETA_MAX_VALUE) {
        this->_eta = eta;
    }
}

int Perceptron::getNIterations(void) const {
    return this->_n_iterations;
}

void Perceptron::setNIterations(int n_iterations) {
    this->_n_iterations = n_iterations;
}
std::vector<float> Perceptron::getWeights(void) const {
    return this->_weights;
}

void Perceptron::setWeights(const std::vector<float>& weights) {
    this->_weights = weights;
}

float Perceptron::weightedSum(std::vector<float> inputXs) const {
    // Constructing a vector with wights expect the first value:
    vector<float> tempWeightsVector(this->_weights.begin() + 1, this->_weights.end());
    return this->_mathOps->dotProduct(inputXs, tempWeightsVector) + this->_weights.at(0);
}

float Perceptron::predict(std::vector<float> inputXs) const {
    float sum = this->weightedSum(inputXs);
    return (sum >= 0.0f) ? 1.0f : -1.0f; // Step activation function
}

void Perceptron::updateWeights(float updateValue, std::vector<float> iInputX) {
    int inputSize = iInputX.size();

    /*
     * Starting from index 1 and not 0, taking into consideration that
     * the first weight is the bias one.
     */
    for (int input = 0; input < inputSize; ++input) {
        this->_weights.at(input+1) = this->_weights.at(input+1) + updateValue * iInputX.at(input);
    }
}

void Perceptron::trainPerceptron(std::vector<std::vector<float>> inputXs, 
                        std::vector<int> expectedYs) {
    int inputXsSize = inputXs.at(0).size();
    // Initialize weights to zero:
    this->_weights = this->_mathOps->initializeVector(inputXsSize + 1, 0.0f); // +1 for bias weight
    
    int lenInputs = inputXs.size();

    // This is the training loop:
    for (int iteration = 0; iteration < this->_n_iterations; ++iteration) {

        int errorCounter = 0;

        /*
         * Iterating over the inputs (x values) and the expected
         * outputs (y values):
         */
        for (int input = 0; input < lenInputs; ++input) {
            /*
             * Excercising the perceptron, by performing a prediction,
             * this will lead to a prediction y, that will be compared
             * with the expected y, and be able to modify the weights
             * and perform better classifications:
             */
            
            float predictedY = this->predict(inputXs.at(input));

            /*
             * Calculate the update value, this value will be used
             * to update the weights in further step, but basically
             * this is done by:
             */
            float updateValue = this->_eta * (expectedYs.at(input) - predictedY);


            this->updateWeights(updateValue, inputXs.at(input));


            // Update the bias:
            this->_weights.at(0) = this->_weights.at(0) + updateValue;

            if (updateValue != 0.0f) {
                errorCounter++;
            }
        }

        this->_errors.push_back(errorCounter);

    
    }
    return;
}
