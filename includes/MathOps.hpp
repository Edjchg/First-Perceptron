#ifndef MATH_OPS_HPP
#define MATH_OPS_HPP

#include <vector>

class MathOps {
    public:
        // Constructor
        MathOps();
        // Destructor
        ~MathOps();

        std::vector<float> initializeVector(int size, float value);
        float dotProduct(const std::vector<float>& vec1, const std::vector<float>& vec2);
};

#endif /* MATH_OPS_HPP */