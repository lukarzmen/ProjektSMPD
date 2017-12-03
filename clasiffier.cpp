#include "clasiffier.h"

clasiffier::clasiffier(){

}
double clasiffier::NearestNeighbour(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify){
    int numberOfCorrectClassifiedObjects = 0;
    int numberOfObjectsToClassify = objectsToClassify.size();
    for(int i=0;i<numberOfObjectsToClassify;i++){
        float minDistance = std::numeric_limits<float>::max();;
        string nameClassifiedClassForObject;
        vector<float> probToClassify = objectsToClassify[i].getFeatures();
        for (auto &objectClass : classifiedObjects)
        {
            int amountOfClassifiedProbs = objectClass.second.size();
            for(int j=0; j<amountOfClassifiedProbs;j++)
            {

                float probDistance = vectorUtil.vectorDistance(objectClass.second[j], probToClassify);
                if(probDistance < minDistance)
                {
                    nameClassifiedClassForObject = objectClass.first;
                    minDistance = probDistance;
                }
            }
        }
        classifiedObjects.find(nameClassifiedClassForObject)->second.push_back(probToClassify);
        if(nameClassifiedClassForObject == objectsToClassify[i].getClassName())
            numberOfCorrectClassifiedObjects++;

    }
    float correctClassifiedObjectsPercentage = ((float)numberOfCorrectClassifiedObjects/(float)numberOfObjectsToClassify)*100.0;
    return (double)correctClassifiedObjectsPercentage;
}
double clasiffier::NearestMean(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify){


    int numberOfCorrectClassifiedObjects = 0;
    int numberOfObjectsToClassify = objectsToClassify.size();

    for(int i=0;i<numberOfObjectsToClassify;i++){
        std::map<string, vector<float>> classesMeans;
        for (auto &objectClass : classifiedObjects)
        {
            std::vector<float> classMean = vectorUtil.calculateColumnMeans(objectClass.second);
            string className = objectClass.first;
            classesMeans.insert(std::pair<string, vector<float>>(className, classMean));
        }

        float minDistance = std::numeric_limits<float>::max();;
        string nameClassifiedClassForObject;
        vector<float> probToClassify = objectsToClassify[i].getFeatures();
        for (auto &classMean : classesMeans)
        {
            float probDistance = vectorUtil.vectorDistance(classMean.second, probToClassify);
            if(probDistance < minDistance)
            {
                nameClassifiedClassForObject = classMean.first;
                minDistance = probDistance;
            }
        }
        classifiedObjects.find(nameClassifiedClassForObject)->second.push_back(probToClassify);
        if(nameClassifiedClassForObject == objectsToClassify[i].getClassName())
            numberOfCorrectClassifiedObjects++;

    }
    float correctClassifiedObjectsPercentage = ((float)numberOfCorrectClassifiedObjects/(float)numberOfObjectsToClassify)*100.0;
    return (double)correctClassifiedObjectsPercentage;
}


double clasiffier::kNearestNeighbour(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify, int k){
    int numberOfCorrectClassifiedObjects = 0;
    int numberOfObjectsToClassify = objectsToClassify.size();
    for(int i=0;i<numberOfObjectsToClassify;i++){
        float minDistance = std::numeric_limits<float>::max();
        string nameClassifiedClassForObject;
        vector<float> probToClassify = objectsToClassify[i].getFeatures();

        std::vector<std::pair<std::string, float>> distancesToClassesProbs;

        for (auto &objectClass : classifiedObjects)
        {
            int amountOfClassifiedProbs = objectClass.second.size();
            for(int j=0; j<amountOfClassifiedProbs;j++)
            {

                float probDistance = vectorUtil.vectorDistance(objectClass.second[j], probToClassify);
                distancesToClassesProbs.push_back(std::pair<std::string, float>(objectClass.first, probDistance));
            }
        }

        sort(distancesToClassesProbs.begin(), distancesToClassesProbs.end(),
             [](const std::pair<std::string, float>& lhs, const std::pair<std::string, float>& rhs) {
            return lhs.second < rhs.second; } );
        std::vector<std::pair<std::string, float>>  rank(distancesToClassesProbs.begin(), distancesToClassesProbs.begin() + k);

        std::map<std::string, int> count_map;
        for(int m = 0; m < rank.size();m++){
            map<string,int>::iterator mapIterator = count_map.find(rank[m].first);
            if(mapIterator == count_map.end())
                count_map.insert(std::pair<std::string, int>(rank[m].first, 0));
            else
                mapIterator->second++;
        }

        int maxCount =  -1;
        foreach(auto &count, count_map){
            int countValue = count.second;
            if(countValue > maxCount)
            {
                maxCount =countValue;
                nameClassifiedClassForObject = count.first;
            }
        }
        classifiedObjects.find(nameClassifiedClassForObject)->second.push_back(probToClassify);
        if(nameClassifiedClassForObject == objectsToClassify[i].getClassName())
            numberOfCorrectClassifiedObjects++;

    }
    float correctClassifiedObjectsPercentage = ((float)numberOfCorrectClassifiedObjects/(float)numberOfObjectsToClassify)*100.0;
    return (double)correctClassifiedObjectsPercentage;
}
double clasiffier::kNearestMean(std::map<string, vector<vector<float>>> classifiedObjects, vector<Object> &objectsToClassify, int k)
{
    int numberOfCorrectClassifiedObjects = 0;
    int numberOfObjectsToClassify = objectsToClassify.size();

    for(int i=0; i<k;i++){

    }
    float correctClassifiedObjectsPercentage = ((float)numberOfCorrectClassifiedObjects/(float)numberOfObjectsToClassify)*100.0;
    return (double)correctClassifiedObjectsPercentage;
}

