#include "ficherelement.h"
ficherElement::ficherElement(){

}
ficherElement::ficherElement(std::vector<int> arrayOfCombinations){
    this->arrayOfCombinations = arrayOfCombinations;
}
void ficherElement::setFischerValue(float fischerValue){
    this->fischerValue = fischerValue;
}

float ficherElement::getFischerValue(){
    return this->fischerValue;
}

std::vector<int>& ficherElement::getVectorOfFeatureCombinations(){
    return this->arrayOfCombinations;
}



