#ifndef FISCHER_H
#define FISCHER_H
#include <string>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include "combination.h"
#include "ficherelement.h"
#include "object_model.h"
#include "object.h"
#include "qglobal.h"
#include <map>

using namespace std;
class Fischer
{
public:
    Fischer();
    map<int,FicherElement> getCombinationsMap(int numberOfFeatures, int dimension);
    vector<Object_model> getObject_Models(vector<Object> &databaseObjects);
private:
    void printCombinations(vector<vector<int>> &arrayOfCombinations);
};

#endif // FISCHER_H
