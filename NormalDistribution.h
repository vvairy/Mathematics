#pragma 
#include "ProbabilityTheory.h"
class NormalDistribution : protected ProbabilityTheory
{
public:
    NormalDistribution(array<vector<double>, 2> componentTable);
private:
    array< vector<double>, 2> componentTable;
    double expectedValue, dispersion;
};