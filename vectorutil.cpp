#include "vectorutil.h"

vectorutil::vectorutil()
{

}

std::vector<std::vector<float>> vectorutil::transpose(std::vector<std::vector<float>> vectorToTranspone)
{
    std::vector<std::vector<float>> transponedVectorOfVectors;
    for (int i = 0; i < vectorToTranspone.front().size(); i++) {
        std::vector<float> innerVector;
        for (int j = 0; j < vectorToTranspone.size(); j++) {
            innerVector.push_back(vectorToTranspone[j][i]);
        }
        transponedVectorOfVectors.push_back(innerVector);
    }
    return transponedVectorOfVectors;
}

float vectorutil::getVectorModule(std::vector<float> vector)
{
    float module =0.0;
    for (int i = 0; i < vector.size(); i++) {
        module += vector[i]*vector[i];
    }
    return sqrt(module);
}

std::vector<std::vector<float>> vectorutil::calculateStds(std::vector<std::vector<float>> vectorsOfVectors, std::vector<float> featureMeans){
    int sizeX = vectorsOfVectors.size();
    int sizeY = vectorsOfVectors.front().size();

    for(int j =0; j< sizeY; j++)
     {
        for (int i = 0; i <sizeX; i++)
        {
            float featureProbStd = vectorsOfVectors.at(i).at(j) - featureMeans[j];
            vectorsOfVectors.at(i).at(j) = fabs(featureProbStd);
        }
    }
    std::vector<std::vector<float>> transponedVectorOfVectors = this->transpose(vectorsOfVectors);
    return transponedVectorOfVectors;
}

std::vector<float> vectorutil::calculateColumnMeans(std::vector<std::vector<float>> vectorsOfVectors){
    std::vector<float> featuresMeans;
    int sizeX = vectorsOfVectors.size();
    int sizeY = vectorsOfVectors.front().size();

    for(int j =0; j< sizeY; j++)
     {
        float sum = 0.0f;
        for (int i = 0; i <sizeX; i++)
            sum+= vectorsOfVectors.at(i).at(j);

        float mean =  sum/sizeY;
        featuresMeans.push_back(mean);
    }
    return featuresMeans;
}

void vectorutil::printVectorOfVectors(std::vector<std::vector<int>> &arrayOfCombinations){
    int sizeOfCombinationsVectorsArray = arrayOfCombinations.size();
    for (int i = 0; i < sizeOfCombinationsVectorsArray; i++)
    {
        int vectorSize = arrayOfCombinations[i].size();
        for (int j = 0; j < vectorSize; j++)
        {
            std::cout << arrayOfCombinations.at(i).at(j);
            if(j < vectorSize - 1)
                std::cout << " ";
            else
                std::cout << ';' << endl;
        }
    }
}

std::vector<std::vector<float>> vectorutil::multiplyMatrix(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B)
{
    std::vector<std::vector<float>> vh;
    for (int i = 0; i < B.size(); i++) {
        std::vector<float> vv;
        for (int j = 0; j < A.front().size(); j++) {
            float temp = 0;
            for (int inner = 0; inner < B[i].size(); inner++) {
                temp += A[inner][j]*B[i][inner];
            }
            vv.push_back(temp);
        }
        vh.push_back(vv);
    }
    return vh;
}

std::vector<std::vector<float>> vectorutil::addMatrix(std::vector<std::vector<float>> v1, std::vector<std::vector<float>> v2){
    std::vector<std::vector<float>> sumVector;
    for (int i = 0; i < v1.size(); i++) {
        std::vector<float> column;
        for (int j = 0; j < v2.front().size(); j++)
        {
            float addedValue = v1.at(i).at(j) + v2.at(i).at(j);
            column.push_back(addedValue);
        }
        sumVector.push_back(column);
    }
    return sumVector;
}
std::vector<float> vectorutil::vectorsSum(vector<float> v1, vector<float> v2)
{
    vector<float> vectorSum;
    for(int i=0;i<v1.front();i++){
        float sum = v1.at(i) + v2.at(i);
        vectorSum.push_back(sum);
    }
    return vectorSum;
}

std::vector<float> vectorutil::vectorsSubstract(vector<float> v1, vector<float> v2)
{
    vector<float> vectorSum;
    for(int i=0;i<v1.front();i++){
        float substract = v1.at(i) - v2.at(i);
        vectorSum.push_back(substract);
    }
    return vectorSum;
}

std::vector<float> vectorutil::vectorsSubstractAbs(vector<float> v1, vector<float> v2)
{
    vector<float> vectorSum;
    for(int i=0;i<v1.front();i++){
        float substractAbs = fabs(v1.at(i) - v2.at(i));
        vectorSum.push_back(substractAbs);
    }
    return vectorSum;
}

float vectorutil::vectorLenght(vector<float> v1){

    float powerSum = 0.0f;
    for(int i=0; i< v1.size();i++){
        float value = v1.at(i);
        powerSum +=  value * value;
    }
    float distance = sqrt(powerSum);
    return distance;
}

float vectorutil::vectorDistance(vector<float> v1, vector<float> v2){
    std::vector<float> substractAbs = vectorsSubstractAbs(v1, v2);
    float vectorDistance = vectorLenght(substractAbs);
    return vectorDistance;
}

std::string vectorutil::vectorToString(vector<int> vectorToParse)
{
    std::stringstream result;
    std::copy(vectorToParse.begin(), vectorToParse.end(), std::ostream_iterator<int>(result, " "));
    return result.str();
}


