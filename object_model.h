#ifndef OBJECT_MODEL_H
#define OBJECT_MODEL_H
#include <string>
#include <vector>

using namespace std;
class Object_model
{
public:
    Object_model(string className);

    void setFeatureAverages(vector<float>);
    void setFeatureStds(vector<float>);

    const vector<vector<float>> getFeatures();
    void setFeatures(vector<vector<float>> arrayOfFeatures);

    const vector<float> getFeatureAverages();
    const vector<float> getFeatureStds();

    const float getFeatureAverageById(int feature_id);
    const float getFeatureStdById(int feature_id);

    const string getClassName();

    bool operator ==(const Object_model& object) const
    {
        return className == object.className;
    }
private:
    vector<std::vector<float>> arrayOfFeatures;
    vector<float> featuresAverages;
    vector<float> featuresStds;
    string className;
};

#endif // OBJECT_MODEL_H
