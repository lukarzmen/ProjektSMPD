#ifndef FICHERELEMENT_H
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <vector>
#define FICHERELEMENT_H


class ficherElement
{
    public:
        ficherElement();
        ~ficherElement(){};
        ficherElement(std::vector<int> arrayOfCombinations);
        void setFischerValue(float fischerValue);
        float getFischerValue(void);
       std::vector<int>& getVectorOfFeatureCombinations();
    private:
        std::vector<int> arrayOfCombinations;
        float fischerValue;
};

#endif // FICHERELEMENT_H
