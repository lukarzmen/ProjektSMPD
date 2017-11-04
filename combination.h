#ifndef COMBINATION_H
#define COMBINATION_H
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <vector>
#endif // COMBINATION_H



namespace Propability {
    class Combinations;
}

class Combinations{
    public:
        Combinations(){};
        ~Combinations(){};
        std::vector<std::vector<int>> generateCombinations(int n, int k);
    private:
        void generateCombinationsUtility(std::vector<std::vector<int> >& ans, std::vector<int>& tmp, int n, int left, int k);
};
