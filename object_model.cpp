#include "object_model.h"

Object_model::Object_model(string className)
{
    this->className = className;
}

void Object_model::setFeatureAverages(vector<float> featureAvgs){
    this->featuresAverages = featureAvgs;
}
void Object_model::setFeatureStds(vector<float> featureStds){
    this->featuresStds = featureStds;
}

const string Object_model::getClassName(){
    return this->className;
}

const vector<float> Object_model::getFeatureAverages(){
    return this-> featuresAverages;
}
const vector<float> Object_model::getFeatureStds(){
    return this->featuresStds;
}

const float Object_model::getFeatureAverageById(int feature_id){
    return this->featuresAverages[feature_id];
}
const float Object_model::getFeatureStdById(int feature_id){
    return this->featuresStds[feature_id];
}
const vector<vector<float>> Object_model::getFeatures(){
    return this->arrayOfFeatures;
}
void Object_model::setFeatures(vector<vector<float>> arrayOfFeatures){
    this->arrayOfFeatures = arrayOfFeatures;
}
