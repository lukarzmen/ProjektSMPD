#ifndef VECTORUTIL_H
#define VECTORUTIL_H

#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
class vectorutil
{
public:
    vectorutil();
    std::vector<std::vector<float>> transpose(std::vector<std::vector<float>> vectorToTranspone);
    float getVectorModule(std::vector<float> vector);
    std::vector<float> calculateColumnMeans(std::vector<std::vector<float>> vectorsOfVectors);
    std::vector<std::vector<float>> calculateStds(std::vector<std::vector<float>> vectorsOfVectors, std::vector<float> featureMeans);
    void printVectorOfVectors(std::vector<std::vector<int>> &arrayOfCombinations);
    std::vector<std::vector<float>> multiplyMatrix(std::vector<std::vector<float>> v1, std::vector<std::vector<float>> v2);
    std::vector<std::vector<float>> addMatrix(std::vector<std::vector<float>> v1, std::vector<std::vector<float>> v2);
    std::vector<float> vectorsSubstract(vector<float> v1, vector<float> v2);
    std::vector<float> vectorsSum(vector<float> v1, vector<float> v2);
    float vectorLenght(vector<float> v1);
    float vectorDistance(vector<float> v1, vector<float> v2);
    std::string vectorToString(vector<int> vectorToParse);
private:
     std::vector<float> vectorsSubstractAbs(vector<float> v1, vector<float> v2);
};

#endif // VECTORUTIL_H
