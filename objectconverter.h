#ifndef OBJECTCONVERTER_H
#define OBJECTCONVERTER_H
#include <string>
#include <vector>
#include "object_model.h"
#include "object.h"
#include "qglobal.h"
#include <map>


using namespace std;
namespace bnu = boost::numeric::ublas;

class objectConverter
{
public:
    objectConverter();
    vector<Object_model> getObject_Models(vector<Object> &databaseObjects);
    map<string, vector<vector<float>>> getObjectsMap(vector<Object> &databaseObjects);
};

#endif // OBJECTCONVERTER_H
