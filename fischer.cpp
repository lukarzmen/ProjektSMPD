#include "fischer.h"

Fischer::Fischer()
{

}

vector<vector<float>> Fischer::calculateCovarianceMatrix(Object_model object, vector<int> arrayFeatureOfCombinations){
    int probSize = object.getFeatureStds(0).size();

    vector<vector<float>> covarianceMatrix;
    for (int i=0; i<probSize; i++){
        vector<float> vectorOfStdsToCalculateCov;
        for(int j=0; j<arrayFeatureOfCombinations.size(); j++)
        {
            int featureID = arrayFeatureOfCombinations.at(j);
            vectorOfStdsToCalculateCov.push_back(object.getFeatureStds(featureID).at(i));
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

std::vector<float> Fischer::getMeansVector(Object_model object, vector<int> arrayFeatureOfCombinations)
{
    vector<float> featureMeans;
    for(int i=0; i< arrayFeatureOfCombinations.size(); i++){
        int featureID = arrayFeatureOfCombinations.at(i);
        float featureMean = object.getFeatureAverage(featureID);
        featureMeans.push_back(featureMean);
    }
    return featureMeans;
}

float Fischer::calculateFischerValue(std::vector<int> featureCombinations, vector<Object_model> objects){
    Object_model classA = objects[0];
    Object_model classB = objects[1];

    std::vector<float> meanA = getMeansVector(classA, featureCombinations);
    std::vector<float> meanB = getMeansVector(classB, featureCombinations);
    std::vector<std::vector<float>> covarianceA = calculateCovarianceMatrix(classA, featureCombinations);
    std::vector<std::vector<float>> covarianceB = calculateCovarianceMatrix(classB, featureCombinations);

    float Sm = vectorUtil.vectorDistance(meanA, meanB);
    std::vector<std::vector<float>> covariance = vectorUtil.addMatrix(covarianceA, covarianceB);
    bnu::matrix<float> covMatrix = matrixUtil.vectorsOfVectorsToMatrix(covariance);

    float Sw = matrixUtil.determinant(covMatrix);
    float fischerValue = Sm/Sw;
    return fischerValue;
}

ficherElement Fischer::getMinFischerElement(Database database, int dimension){
    int numberOfFeatures = database.getNoFeatures();
    vector<Object> all_obj = database.getObjects();

    float minFischerValue = std::numeric_limits<float>::max();
    int minFischerIndex = 0;
    std::map<int,ficherElement> combinationsMap = combinations.getCombinationsMap(numberOfFeatures, dimension);
    std::vector<Object_model> objectModels = objectconverter.getObject_Models(all_obj);

    for (auto &combination : combinationsMap)
    {
        const std::vector<int> arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();

        float fischerValue = calculateFischerValue(arrayFeatureOfCombinations, objectModels);
        if(fischerValue < minFischerValue)
        {
            minFischerValue = fischerValue;
            minFischerIndex = combination.first;
        }
        combination.second.setFischerValue(fischerValue);
    }
    ficherElement minFischerElement = combinationsMap.at(minFischerIndex);
    return minFischerElement;
}

ficherElement Fischer::getMinFischerElementSFC(Database database, int dimension){
    int numberOfFeatures = database.getNoFeatures();
    vector<Object> all_obj = database.getObjects();
    std::vector<Object_model> objectModels = objectconverter.getObject_Models(all_obj);

    vector<int> maxCombinationFeatures;
    std::map<int,ficherElement> combinationsMap;
    int minFischerIndex = 0;

    for(int i = 0; i < dimension; i++)
    {
        if(i == 0)
            combinationsMap = combinations.getCombinationsMap(64,1);
        else
        {
            maxCombinationFeatures.push_back(minFischerIndex);
            combinationsMap = combinations.getCombinationsMap(numberOfFeatures,maxCombinationFeatures);
        }

        float minFischerValue = std::numeric_limits<float>::max();

        for (auto &combination : combinationsMap)
        {
            const std::vector<int> arrayFeatureOfCombinations = combination.second.getVectorOfFeatureCombinations();
            float fischerValue = calculateFischerValue(arrayFeatureOfCombinations, objectModels);
            if(fischerValue < minFischerValue)
            {
                minFischerValue = fischerValue;
                minFischerIndex = combination.first;
            }
            combination.second.setFischerValue(fischerValue);
        }
    }
    ficherElement minFischerElement = combinationsMap.at(minFischerIndex);
    return minFischerElement;
}


