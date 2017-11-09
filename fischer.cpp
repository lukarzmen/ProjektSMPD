#include "fischer.h"

Fischer::Fischer()
{

}


void Fischer::printCombinations(std::vector<std::vector<int>> &arrayOfCombinations){
    int sizeOfCombinationsVectorsArray = arrayOfCombinations.size();
    for (int i = 0; i < sizeOfCombinationsVectorsArray; i++)
    {
        int vectorSize = arrayOfCombinations[i].size();
        for (int j = 0; j < vectorSize; j++)
        {
            std::cout << arrayOfCombinations.at(i).at(j);
            if(j < vectorSize - 1)
                std::cout << " ";
            else
                std::cout << ';' << endl;
        }
    }
}

map<int,FicherElement> Fischer::getCombinationsMap(int numberOfFeatures, int dimension){
    Combinations* combinations = new Combinations();
    vector<vector<int>> arrayOfCombinations = combinations->generateCombinations(numberOfFeatures, dimension);
    delete combinations;
    //for developer tests
    printCombinations(arrayOfCombinations);

    map<int,FicherElement> combinationsMap;

    for (int i = 0; i < arrayOfCombinations.size(); i++)
    {
        FicherElement ficherElementToInsert = FicherElement(arrayOfCombinations[i]);
        combinationsMap.insert(pair<int, FicherElement>(i, ficherElementToInsert));
    }

    return combinationsMap;
}

vector<Object_model> Fischer::getObject_Models(vector<Object> &databaseObjects){
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

    vector<Object_model> objects;
    foreach (auto &classWithFeatures, classesWithFeatures) {
        string className = classWithFeatures.first;
        vector<std::vector<float>> arrayOfFeatures = classWithFeatures.second;

        Object_model object_model = Object_model(className);
        object_model.setFeatures(arrayOfFeatures);
        objects.push_back(object_model);
    }

    return objects;
}
