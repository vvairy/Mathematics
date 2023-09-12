#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
using std::cin; using std::cout; using std::endl;
using std::array; using std::vector;
class ProbabilityTheory
{
public:
    array <vector<double>, 2> componentTable;
    double expectedValue = 0, dispersion = 0;
    const double PI = 3.14159;
    const double EXP = 2.71828;
protected:
    virtual double computeExpectedValue();
    virtual double computeDispersion();
    double localLaplassFunction(double arg);
    static unsigned numberOfCombinations(unsigned NumKits, unsigned NumElements);
    static unsigned numberOfAccommodations(unsigned NumKits, unsigned NumElements);
    static unsigned factorial(unsigned Number);
    static double getCountInVec(double number, vector<double>& vec);
};