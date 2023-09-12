#pragma once
#include "ProbabilityTheory.h"
#include<map>
using std::map;
class Correlation : ProbabilityTheory
{
public:

    Correlation(array<vector<double>, 2> pairs);
    map <const char*, double> numberCharacteristics;
private:

    double computeTwoDimensionalExpectedValue();
    double computeExpectedValueComponent(array <vector<double>, 2>& componentTable);
    double computeDispersionComponent(array <vector<double>, 2>& componentTable);
    void fillNumberCharacteristics();
    array <vector<double>, 2> getComponentTable(vector<double>& row);
    vector <double> getUniqueAndSort(vector<double>& row);
    void tableCountOfSamePairs();
    vector <vector <double>> getCorrelationTable();
    double getCorrelationMoment();
    bool isCorrelate();
    double getCorrelationKoefficient();
    void strenghtOfCorrelation();
    void makeLineRegression();

    size_t experimentsCount_;
    array<vector<double>, 2> pairs;
    vector<vector <double>> correlationTable;
    array <vector <double>, 2> componentTableX;
    array <vector <double>, 2> componentTableY;
    std::map <std::array<double, 2>, unsigned> countOfEachPair;
};