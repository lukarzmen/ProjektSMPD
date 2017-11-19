#ifndef OBJECT_MODEL_H
#define OBJECT_MODEL_H
#include <string>
#include <vector>
#include "matrixutil.h"
#include "vectorutil.h"

using namespace std;
class Object_model
{
public:
    Object_model(string className, std::vector<std::vector<float>> arrayOfFeatures);

    vector<float> getFeatureStds(int featureId);
    float getFeatureAverage(int averageId);
    int getFeaturesCount();
    const string getClassName();

    bool operator ==(const Object_model& object) const
    {
        return className == object.className;
    }
private:
    vector<float> featureAverages;
    vector<vector<float>> featureStds;
    string className;
    vectorutil vectorUtil;
};

#endif // OBJECT_MODEL_H
