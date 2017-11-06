#include "ficherelement.h"

FicherElement::FicherElement(std::vector<int> *arrayOfCombinations){
    this->arrayOfCombinations = arrayOfCombinations;
}
void FicherElement::setFischerValue(float fischerValue){
    this->fischerValue = fischerValue;
}

float FicherElement::getFischerValue(){
    return this->fischerValue;
}

const std::vector<int> *FicherElement::getVectorOfFeatureCombinations(){
    return this->arrayOfCombinations;
}

