#ifndef FICHERELEMENT_H
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <vector>
#define FICHERELEMENT_H



namespace Statistics {
    class FicherElement;
}

class FicherElement
{
public:
    FicherElement(){};
    ~FicherElement(){};
    FicherElement(std::vector<int> *arrayOfCombinations);
    void setFischerValue(float fischerValue);
    float getFischerValue(void);
   const std::vector<int> *getVectorOfFeatureCombinations();
private:
    int id;
    std::vector<int> *arrayOfCombinations;
    float fischerValue;
};

#endif // FICHERELEMENT_H
