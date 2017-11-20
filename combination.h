#ifndef COMBINATION_H
#define COMBINATION_H
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <vector>
#include <map>
#include "ficherelement.h"
#endif // COMBINATION_H


class Combinations
{
public:
    Combinations();
    ~Combinations();
    std::map<int,ficherElement> getCombinationsMap(int numberOfFeatures, int dimension);
private:
    std::vector<std::vector<int>> generateCombinations(int n, int k);
    void generateCombinationsUtility(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k);
};
