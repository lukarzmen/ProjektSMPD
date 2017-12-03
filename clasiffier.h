#ifndef CLASIFFIER_H
#include <vector>
#include "object.h"
#include "vectorutil.h"
#include <map>
#include <limits>
#include "qglobal.h"
#define CLASIFFIER_H


class clasiffier
{
public:
    clasiffier();
    double NearestNeighbour(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify);
    double NearestMean(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify);
    double kNearestNeighbour(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify, int k);
    double kNearestMean(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify, int k);
private:
   vectorutil vectorUtil;
};

#endif // CLASIFFIER_H
