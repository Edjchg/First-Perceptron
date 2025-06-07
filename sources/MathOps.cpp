#include <iostream>
#include <stdexcept>

#include "MathOps.hpp"

using namespace std;

MathOps::MathOps() {
    // Constructor implementation:
}

MathOps::~MathOps() {
    // Destructor implementation:
}

vector<float> MathOps::initializeVector(int size, float value) {
    return vector<float>(size, value);
}

float MathOps::dotProduct(const vector<float>& vec1, const vector<float>& vec2) {
    int vec1Size = vec1.size();
    int vec2Size = vec2.size();
    if (vec1Size != vec2Size) {
        cout << "Vec 1 size: " << vec1Size << ", and Vec 2 size: " << vec2Size << endl;
        throw std::invalid_argument("Vectors must be of the same size for dot product.");
    }
    
    float result = 0.0f;
    for (int i = 0; i < vec1Size; ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}