#ifndef OBJECT_MODEL_H
#define OBJECT_MODEL_H
#include <string>
#include <vector>
#include "matrixutil.h"

using namespace std;
class Object_model
{
public:
    Object_model(string className);
    bnu::matrix<float> getFeatures();
    void setFeatures(vector<vector<float>> arrayOfFeatures);

    vector<float> getFeature(int id);
    getFeatureAverage(int id);

    const string getClassName();

    bool operator ==(const Object_model& object) const
    {
        return className == object.className;
    }
private:
    bnu::matrix<float> arrayOfFeatures;
    string className;
    matrixutil matrix;
};

#endif // OBJECT_MODEL_H
