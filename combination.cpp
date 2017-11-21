#include "combination.h"

Combinations::Combinations(){}
Combinations::~Combinations(){}

void Combinations::generateCombinationsUtility(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k)
{
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }
    for (int i = left; i <= n; ++i)
    {
        tmp.push_back(i);
        generateCombinationsUtility(ans, tmp, n, i + 1, k - 1);
        tmp.pop_back();
    }
}

std::vector<std::vector<int>> Combinations::generateCombinationsFixedlPlusOne(int n, std::vector<int> fixedElements)
{
    std::vector<std::vector<int>> vectorOfCombinations;
    for(int i =0; i< n; i++)
    {
        if(!(std::find(fixedElements.begin(), fixedElements.end(), i) != fixedElements.end()))
        {
            std::vector<int> combination;
            combination.swap(fixedElements);
            combination.push_back(i);
            vectorOfCombinations.push_back(combination);
        }
    }
    return vectorOfCombinations;
}

std::vector<std::vector<int>> Combinations::generateCombinations(int n, int k)
{
    std::vector<std::vector<int> > ans;
    std::vector<int> tmp;
    generateCombinationsUtility(ans, tmp, n, 1, k);
    return ans;
}

std::map<int,ficherElement>  Combinations::getCombinationsMap(int numberOfFeatures, int dimension){
    std::vector<std::vector<int>> arrayOfCombinations = generateCombinations(numberOfFeatures, dimension);

    std::map<int,ficherElement> combinationsMap;

    for (int i = 0; i < arrayOfCombinations.size(); i++)
    {
        ficherElement ficherElementToInsert = ficherElement(arrayOfCombinations[i]);
        combinationsMap.insert(std::pair<int, ficherElement>(i, ficherElementToInsert));
    }
    return combinationsMap;
}

std::map<int,ficherElement> Combinations::getCombinationsMap(std::vector<std::vector<int>> vectorOfCombinations){
    std::map<int,ficherElement> combinationsMap;

    for (int i = 0; i < vectorOfCombinations.size(); i++)
    {
        ficherElement ficherElementToInsert = ficherElement(vectorOfCombinations[i]);
        combinationsMap.insert(std::pair<int, ficherElement>(i, ficherElementToInsert));
    }
    return combinationsMap;
}

std::map<int,ficherElement>  Combinations::getCombinationsMap(int numberOfFeatures, std::vector<int> fixedElements){
    std::vector<std::vector<int>> arrayOfCombinations = generateCombinationsFixedlPlusOne(numberOfFeatures, fixedElements);

    std::map<int,ficherElement> combinationsMap;

    for (int i = 0; i < arrayOfCombinations.size(); i++)
    {
        ficherElement ficherElementToInsert = ficherElement(arrayOfCombinations[i]);
        combinationsMap.insert(std::pair<int, ficherElement>(i, ficherElementToInsert));
    }
    return combinationsMap;
}


