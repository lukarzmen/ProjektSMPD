#ifndef OBJECTCLUSTER_H
#include <string>
#include <vector>
#define OBJECTCLUSTER_H


class objectCluster
{
public:
    objectCluster(std::string className);
    std::string getClassName;
    double getAverage();
    void addProb(std::vector<double> prob);
    void setProbs(std::vector<std::vector<double>> probs);
    std::vector<std::vector<double>> getProbs(std::vector<double> prob);
private:
    std::string className;
    std::vector<std::vector<double>> objects;

};

#endif // OBJECTCLUSTER_H
