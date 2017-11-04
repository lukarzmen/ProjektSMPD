#include "combination.h"

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

std::vector<std::vector<int>> Combinations::generateCombinations(int n, int k)
{
    std::vector<std::vector<int> > ans;
    std::vector<int> tmp;
    generateCombinationsUtility(ans, tmp, n, 1, k);
    return ans;
}


