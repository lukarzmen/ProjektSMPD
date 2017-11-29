#include "fischer.h"

Fischer::Fischer()
{

}

vector<vector<float>> Fischer::calculateCovarianceMatrix(Object_model &object, vector<int> &arrayFeatureOfCombinations){
    int probSize = object.getFeatureVariances(0).size();

    vector<vector<float>> covarianceMatrix;
    for (int i=0; i<probSize; i++){
        vector<float> vectorOfStdsToCalculateCov;
        for(int j=0; j<arrayFeatureOfCombinations.size(); j++)
        {
            int featureID = arrayFeatureOfCombinations.at(j);
            float variance = object.getFeatureVariances(featureID).at(i);
            vectorOfStdsToCalculateCov.push_back(variance);
        }
        vector<vector<float>> covarianceVector;
        covarianceVector.push_back(vectorOfStdsToCalculateCov);
        vector<vector<float>> transposedCovarianceVector;
        transposedCovarianceVector = vectorUtil.transpose(covarianceVector);

        vector<vector<float>> powerOfCovarianceVectors =vectorUtil.multiplyMatrix(covarianceVector,transposedCovarianceVector);
        if(covarianceMatrix.size() == 0)
            covarianceMatrix = powerOfCovarianceVectors;
        else
            covarianceMatrix = vectorUtil.addMatrix(covarianceMatrix, powerOfCovarianceVectors);
    }
    return covarianceMatrix;
}

std::vector<float> Fischer::getMeansVector(Object_model &object, vector<int> &arrayFeatureOfCombinations)
{
    vector<float> featureMeans;
    for(int i=0; i< arrayFeatureOfCombinations.size(); i++){
        int featureID = arrayFeatureOfCombinations.at(i);
        float featureMean = object.getFeatureAverage(featureID);
        featureMeans.push_back(featureMean);
    }
    return featureMeans;
}

float Fischer::calculateFischerValue(std::vector<int> &featureCombinations, vector<Object_model> &objects){
    Object_model classA = objects[0];
    Object_model classB = objects[1];
    float fischerValue = 0.0f;

    std::vector<float> meanA = getMeansVector(classA, featureCombinations);
    std::vector<float> meanB = getMeansVector(classB, featureCombinations);
    std::vector<std::vector<float>> covarianceA = calculateCovarianceMatrix(classA, featureCombinations);
    std::vector<std::vector<float>> covarianceB = calculateCovarianceMatrix(classB, featureCombinations);

    float Sm = vectorUtil.vectorDistance(meanA, meanB);

    if (featureCombinations.size() > 1)
    {
        std::vector<std::vector<float>> covariance = vectorUtil.addMatrix(covarianceA, covarianceB);
        bnu::matrix<float> covMatrix = matrixUtil.vectorsOfVectorsToMatrix(covariance);

        float Sw = matrixUtil.determinant(covMatrix);
        fischerValue = Sm/Sw;
    }
    else
    {
        float varianceA = covarianceA.front().front();
        float varianceB = covarianceB.front().front();
        float Sw = sqrt(varianceA) + sqrt(varianceB);
        fischerValue = Sm/Sw;
    }
    return fischerValue;
}

ficherElement Fischer::getBestFischerElement(Database &database, int dimension){
    int numberOfFeatures = database.getNoFeatures();
    vector<Object> all_obj = database.getObjects();

    float maxFischerValue = std::numeric_limits<float>::min();
    int maxFischerIndex = 0;
    std::map<int,ficherElement> combinationsMap = combinations.getCombinationsMap(numberOfFeatures, dimension);
    std::vector<Object_model> objectModels = objectconverter.getObject_Models(all_obj);

    for (auto &combination : combinationsMap)
    {
        std::vector<int> arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();

        float fischerValue = calculateFischerValue(arrayFeatureOfCombinations, objectModels);
        if(fischerValue > maxFischerValue)
        {
            maxFischerValue = fischerValue;
            maxFischerIndex = combination.first;
        }
        combination.second.setFischerValue(fischerValue);
    }
    ficherElement bestFischerElement = combinationsMap.at(maxFischerIndex);
    return bestFischerElement;
}

ficherElement Fischer::getBestFischerElementSFC(Database &database, int dimension){
    int numberOfFeatures = database.getNoFeatures();
    vector<Object> all_obj = database.getObjects();
    std::vector<Object_model> objectModels = objectconverter.getObject_Models(all_obj);

    vector<int> maxCombinationFeatures;
    std::map<int,ficherElement> combinationsMap;
    int maxFischerIndex = 0;

    for(int i = 0; i < dimension; i++)
    {
        if(i == 0)
            combinationsMap = combinations.getCombinationsMap(numberOfFeatures,1);
        else
        {
            maxCombinationFeatures = combinationsMap.at(maxFischerIndex).getVectorOfFeatureCombinations();
            combinationsMap = combinations.getCombinationsMap(numberOfFeatures,maxCombinationFeatures);
        }

        float maxFischerValue = std::numeric_limits<float>::min();

        for (auto &combination : combinationsMap)
        {
            std::vector<int> arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();
            float fischerValue = calculateFischerValue(arrayFeatureOfCombinations, objectModels);
            if(fischerValue > maxFischerValue)
            {
                maxFischerValue = fischerValue;
                maxFischerIndex = combination.first;
            }
            combination.second.setFischerValue(fischerValue);
        }

    }
    ficherElement bestFischerElement = combinationsMap.at(maxFischerIndex);
    return bestFischerElement;
}


