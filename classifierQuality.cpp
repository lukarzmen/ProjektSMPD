#include "classifierQuality.h"

ClassifierQuality::ClassifierQuality()
{

}


float ClassifierQuality::BootstrapClassifier(vector<Object> all_obj, int intervalsAmount){
    random_shuffle(all_obj.begin(), all_obj.end());
    vector<vector<Object>> sliceOfVectors;

    int vectorSize = all_obj.size();
    int partSize =vectorSize/intervalsAmount;

    for(int i=0; i< intervalsAmount; i+=partSize){
        if(i >vectorSize )
            i=vectorSize;
        vector<Object> slice(all_obj.begin() + i, all_obj.end() + i+partSize);
        sliceOfVectors.push_back(slice);
    }

    float sum = 0.0f;
    return 0.0f;
}
float ClassifierQuality::CrossValidationClassifier(vector<Object> all_obj){
    random_shuffle(all_obj.begin(), all_obj.end());

    int objectVectorSize = all_obj.size();
    vector<int> randomIndexes;
    for(int i = 0; i < objectVectorSize; i++)
    {
        int randomIndex = rand() % objectVectorSize + 1; ;

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

//    for(int i = 0; i < all_obj.size(); i++)
//        for(int j = 0; j < randomIndexes.size(); j++)
//            bootstrapTrainingSet.push_back();

    return 0.0f;
}
