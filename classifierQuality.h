#ifndef CLASSIFIERDATASETS_H
#include <vector>
#include "object.h"
#include "classifier.h"
#include <algorithm>
#include <cstdlib>
#include "clasiffier.h"
#define CLASSIFIERDATASETS_H

using namespace std;

class ClassifierQuality
{
public:
    ClassifierQuality();
    float BootstrapClassifier(vector<Object> all_obj, int intervalsAmount);
    float CrossValidationClassifier(vector<Object> all_obj);
private:
     clasiffier clasifier;
};


#endif // CLASSIFIERDATASETS_H
