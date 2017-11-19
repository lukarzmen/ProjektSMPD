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
#include "vectorutil.h"
#include "matrixutil.h"

using namespace std;
namespace bnu = boost::numeric::ublas;

class Fischer
{
public:
    Fischer();
    map<int,FicherElement> getCombinationsMap(int numberOfFeatures, int dimension);
    vector<Object_model> getObject_Models(vector<Object> &databaseObjects);
    vector<vector<float>> calculateCovarianceMatrix(Object_model object, vector<int> arrayFeatureOfCombinations);
    vector<float> getMeansVector(Object_model object, vector<int> arrayFeatureOfCombinations);
private:
    vectorutil vectorUtil;
    matrixutil matrixUtil;
    map<string, vector<vector<float>>> getObjectsMap(vector<Object> &databaseObjects);
};

#endif // FISCHER_H
