#include "classifier_object.h"

classifier_object::classifier_object(vector<Object> trainingSet, vector<Object> testSet)
{
    this->testSet = testSet;
    this->trainingSet = trainingSet;
}
vector<Object> classifier_object::getTrainingSet()
{
    return this->trainingSet;
}
vector<Object> classifier_object::getTestSet()
{
    return this->testSet;
}
