#include "objectconverter.h"

objectConverter::objectConverter()
{

}

std::vector<Object_model> objectConverter::getObject_Models(vector<Object> &databaseObjects){

    std::map<string, vector<vector<float>>> classesWithFeatures = getObjectsMap(databaseObjects);
    vector<Object_model> objects;
    foreach (auto &classWithFeatures, classesWithFeatures) {
        string className = classWithFeatures.first;
        vector<std::vector<float>> arrayOfFeatures = classWithFeatures.second;

        Object_model object_model = Object_model(className, arrayOfFeatures);
        objects.push_back(object_model);
    }

    return objects;
}

map<string, vector<vector<float>>> objectConverter::getObjectsMap(vector<Object> &databaseObjects){
    map<string, vector<vector<float>>> classesWithFeatures;

    for (int i = 0; i < databaseObjects.size(); i++) {
        string classNameKey = databaseObjects[i].getClassName();
        vector<float> features = databaseObjects[i].getFeatures();

        map<string,vector<vector<float>>>::iterator mapIterator = classesWithFeatures.find(classNameKey);
        if(mapIterator == classesWithFeatures.end())
        {
            std::vector<std::vector<float>> newArrayOfFeatures;
            newArrayOfFeatures.push_back(features);
            pair<string, vector<vector<float>>> newMapElement = pair<string, vector<vector<float>>>(classNameKey, newArrayOfFeatures);
            classesWithFeatures.insert(newMapElement);
        }
        else
            mapIterator->second.push_back(features);
    }
    return classesWithFeatures;
}
