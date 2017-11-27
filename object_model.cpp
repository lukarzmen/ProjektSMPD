#include "object_model.h"

Object_model::Object_model(string className, std::vector<std::vector<float>> arrayOfFeatures)
{
    this->className = className;
    this->featureAverages = this->vectorUtil.calculateColumnMeans(arrayOfFeatures);
    this->featureVariances = this->vectorUtil.calculateVariances(arrayOfFeatures, this->featureAverages);
}


const string Object_model::getClassName(){
    return this->className;
}

int Object_model::getFeaturesCount()
{
    return featureAverages.size();
}
vector<float>& Object_model::getFeatureVariances(int featureId){
    return  featureVariances.at(featureId);
}
float Object_model::getFeatureAverage(int averageId){
    return featureAverages.at(averageId);
}



