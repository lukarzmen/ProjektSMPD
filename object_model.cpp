#include "object_model.h"

Object_model::Object_model(string className)
{
    this->className = className;
}

const string Object_model::getClassName(){
    return this->className;
}

bnu::matrix<float> Object_model::getFeatures(){
    return this->arrayOfFeatures;
}

void Object_model::setFeatures(std::vector<std::vector<float>> arrayOfFeatures){

    this->arrayOfFeatures = this->matrix.vectorsOfVectorsToMatrix(arrayOfFeatures);
}




