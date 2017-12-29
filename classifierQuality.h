#ifndef CLASSIFIERDATASETS_H
#include <vector>
#include "object.h"
#include "classifier.h"
#include <algorithm>
#include <cstdlib>
#include "clasiffier.h"
#include "classifier_object.h"
#define CLASSIFIERDATASETS_H

using namespace std;

class ClassifierQuality
{
public:
    ClassifierQuality();
    classifier_object Bootstrap(vector<Object> &all_obj);
    vector<vector<Object>> CrossValidation(vector<Object> &all_obj, int intervalsAmount);
private:
     clasiffier clasifier;
};


#endif // CLASSIFIERDATASETS_H
