#ifndef FISCHER_H
#include <string>
#include <vector>
#include "object_model.h"
#include "object.h"
#include "qglobal.h"
#include <map>
#include "vectorutil.h"
#include "matrixutil.h"
#include "objectconverter.h"
#include "ficherelement.h"
#include "combination.h"
#include "database.h"
#define FISCHER_H

using namespace std;
namespace bnu = boost::numeric::ublas;

class Fischer
{
public:
    Fischer();
    ficherElement getMinFischerElement(Database database, int dimension);
private:
    vectorutil vectorUtil;
    matrixutil matrixUtil;
    objectConverter objectconverter;
    Combinations combinations;
    vector<float> getMeansVector(Object_model object, vector<int> arrayFeatureOfCombinations);
    vector<vector<float>> calculateCovarianceMatrix(Object_model object, vector<int> arrayFeatureOfCombinations);
    float calculateFischerValue(std::vector<int> featureCombinations, vector<Object_model> objects);
};

#endif // FISCHER_H
