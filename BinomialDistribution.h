#pragma once
#include "ProbabilityTheory.h"
class BinomialDistribution : ProbabilityTheory
{
public:
    BinomialDistribution(double probabiliy, int countOfExperiments);

    double computeExpectedValue() override;
    double computeDispersion() override;
    array<vector<double>, 2> fillComponentTable();
    double n, p, q;
    array <vector<double>, 2> componentTable;
};
