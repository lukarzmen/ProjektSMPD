#include "classifierQuality.h"

ClassifierQuality::ClassifierQuality()
{

}


classifier_object ClassifierQuality::Bootstrap(vector<Object> &all_obj){

    random_shuffle(all_obj.begin(), all_obj.end());

    int objectVectorSize = all_obj.size();
    vector<int> randomIndexes;
    for(int i = 0; i < objectVectorSize; i++)
    {
        int randomIndex = rand() % objectVectorSize + 1;
        bool isUnique = true;
        for(int j = 0; j < randomIndexes.size(); j++)
            if(randomIndex == randomIndexes[j])
            {
                isUnique = false;
                break;
            }
        if(isUnique)
            randomIndexes.push_back(randomIndex);
    }

    std::vector<Object> bootstrapTrainingSet;
    std::vector<Object> bootstrapTestSet;

    for(int i = 0; i < objectVectorSize; i++)
    {
        bool isUnique = true;
        for(int j = 0; j < randomIndexes.size(); j++)
        {
            if(i == randomIndexes[j])
            {
                isUnique = false;
                bootstrapTrainingSet.push_back(all_obj[i]);
                break;
            }
        }
        if(isUnique)
            bootstrapTestSet.push_back(all_obj[i]);
    }
    return classifier_object(bootstrapTrainingSet, bootstrapTestSet);
}

vector<vector<Object>> ClassifierQuality::CrossValidation(vector<Object> &all_obj, int intervalsAmount){
    random_shuffle(all_obj.begin(), all_obj.end());
    vector<vector<Object>> sliceOfVectors;

    int vectorSize = all_obj.size();
    if(intervalsAmount <= 0)
        intervalsAmount = 1;
    int partSize =vectorSize/intervalsAmount;

    for(int i=0; i< vectorSize; i+=partSize){
        int end = i+partSize;
        if(end >vectorSize )
            end=vectorSize;
        vector<Object> slice(all_obj.begin() + i, all_obj.begin() + end);
        sliceOfVectors.push_back(slice);
    }

    return sliceOfVectors;
}
