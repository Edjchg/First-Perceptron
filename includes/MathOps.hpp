#ifndef MATH_OPS_HPP
#define MATH_OPS_HPP

#include <vector>

/**
 * @brief Class for performing mathematical operations
 *
 * This class provides methods for initializing vectors and performing
 * dot products. It is designed to be used in the context of a perceptron
 * or other machine learning algorithms where vector operations are common.
 */
class MathOps {
    public:
        // Constructor
        MathOps();
        // Destructor
        ~MathOps();

        /**
         * @brief This function initializes a vector to a certain value and a size.
         *
         * @param[in] size int representing the size of the vector.
         *
         * @param[in] value float representing the value of the vector will be initialized
         *            with.
         *
         * @return float vector initialized with the requested value and size.
         */
        std::vector<float> initializeVector(int size, float value);

        /**
         * @brief This vector performs a dot product over 2 vectors.
         *
         * @param[in] vec1 vector 1.
         *
         * @param[in] vec2 vector 2.
         *
         * @return float with the resulting dot product.
         */
        float dotProduct(const std::vector<float>& vec1, const std::vector<float>& vec2);
};

#endif /* MATH_OPS_HPP */
