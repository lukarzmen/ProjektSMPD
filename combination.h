#ifndef COMBINATION_H
#define COMBINATION_H
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <map>
#include "ficherelement.h"
#include <algorithm>
#endif // COMBINATION_H


class Combinations
{
public:
    Combinations();
    ~Combinations();
    std::map<int,ficherElement> getCombinationsMap(std::vector<std::vector<int>> vectorOfCombinations);
    std::map<int,ficherElement> getCombinationsMap(int numberOfFeatures, int dimension);
    std::map<int,ficherElement> getCombinationsMap(int numberOfFeatures, std::vector<int> fixedElements);
    std::vector<std::vector<int>> generateCombinations(int n, int k);

private:
    void generateCombinationsUtility(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k);
    std::vector<std::vector<int>> generateCombinationsFixedlPlusOne(int n, std::vector<int> fixedElements);
};
