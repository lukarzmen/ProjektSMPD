#ifndef CLASSIFIER_OBJECT_H
#include <vector>
#include "object.h"
#define CLASSIFIER_OBJECT_H

using namespace std;
class classifier_object
{
public:
    classifier_object(vector<Object> trainingSet, vector<Object> testSet);
   vector<Object> getTrainingSet();
   vector<Object> getTestSet();
private:
    vector<Object> trainingSet;
    vector<Object> testSet;
};


#endif // CLASSIFIER_OBJECT_H
