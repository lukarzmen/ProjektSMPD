#include "fischer.h"

Fischer::Fischer()
{

}

map<int,FicherElement> Fischer::getCombinationsMap(int numberOfFeatures, int dimension){
    Combinations* combinations = new Combinations();
    vector<vector<int>> arrayOfCombinations = combinations->generateCombinations(numberOfFeatures, dimension);
    delete combinations;

    map<int,FicherElement> combinationsMap;

    for (int i = 0; i < arrayOfCombinations.size(); i++)
    {
        FicherElement ficherElementToInsert = FicherElement(arrayOfCombinations[i]);
        combinationsMap.insert(pair<int, FicherElement>(i, ficherElementToInsert));
    }

    return combinationsMap;
}

vector<Object_model> Fischer::getObject_Models(vector<Object> &databaseObjects){

    map<string, vector<vector<float>>> classesWithFeatures = getObjectsMap(databaseObjects);
    vector<Object_model> objects;
    foreach (auto &classWithFeatures, classesWithFeatures) {
        string className = classWithFeatures.first;
        vector<std::vector<float>> arrayOfFeatures = classWithFeatures.second;

        Object_model object_model = Object_model(className, arrayOfFeatures);
        objects.push_back(object_model);
    }

    return objects;
}

map<string, vector<vector<float>>> Fischer::getObjectsMap(vector<Object> &databaseObjects){
    map<string, vector<vector<float>>> classesWithFeatures;

    for (int i = 0; i < databaseObjects.size(); i++) {
        string classNameKey = databaseObjects[i].getClassName();
        vector<float> features = databaseObjects[i].getFeatures();

        map<string,vector<vector<float>>>::iterator mapIterator = classesWithFeatures.find(classNameKey);
        if(mapIterator == classesWithFeatures.end())
        {
            std::vector<std::vector<float>> newArrayOfFeatures;
            newArrayOfFeatures.push_back(features);
            pair<string, vector<vector<float>>> newMapElement = pair<string, vector<vector<float>>>(classNameKey, newArrayOfFeatures);
            classesWithFeatures.insert(newMapElement);
        }
        else
            mapIterator->second.push_back(features);
    }
    return classesWithFeatures;
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

        //todo: do odwrócenia w metodzie multiply matrix
        vector<vector<float>> powerOfCovarianceVectors =vectorUtil.multiplyMatrix(transposedCovarianceVector, covarianceVector);
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


