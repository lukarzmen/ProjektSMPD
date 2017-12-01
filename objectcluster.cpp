#include "objectcluster.h"



objectCluster::objectCluster(std::string className){

}
std::string objectCluster::getClassName(){
    return this->className;
}
double objectCluster::getAverage(){
    return 0;
}
void objectCluster::addProb(std::vector<double> prob){}
void objectCluster::setProbs(std::vector<std::vector<double>> probs){}
std::vector<std::vector<double>> objectCluster::getProbs(std::vector<double> prob){
    return this->objects;
}
