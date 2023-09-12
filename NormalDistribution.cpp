#include "NormalDistribution.h"
#include <array>
using std::array;
NormalDistribution::NormalDistribution(array<vector<double>, 2> componentTable) : componentTable(componentTable)
{
    this->expectedValue = computeExpectedValue();
    this->dispersion = computeDispersion();
}
