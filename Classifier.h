#include "database.h"

class Classifier
{
	
	public:
                Classifier( const Database &trainSet, const Database &testSet ) : trainingSet(trainSet), testSet(testSet){}
		
		virtual void train() = 0;
		
		virtual float test() = 0; 
		
	private:
	
                Database trainingSet;
                Database testSet;
		
	
};
