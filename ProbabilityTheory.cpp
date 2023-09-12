#include "ProbabilityTheory.h"
const double PI = 3.14159;
const double EXP = 2.71828;
double ProbabilityTheory::computeExpectedValue() //выборочное среднее составляющЕЙ (1) - аналог математического ожидания для выборки
{
    double expectedValue = 0;
    for (size_t i = 0; i < size(this->componentTable[0]); i++)
        expectedValue += this->componentTable[0][i] * this->componentTable[1][i];
    return expectedValue;
}

double ProbabilityTheory::computeDispersion() //дисперсия - величина, показывающая среднее отклонение случайной величины от матожидания
{
    double Dispersion = 0;
    for (size_t i = 0; i < size(this->componentTable[0]); i++)
        Dispersion += pow(this->componentTable[0][i], 2) * this->componentTable[1][i];
    Dispersion -= pow(this->expectedValue, 2); // D[x] = M[x^2] - M^2[x]
    return Dispersion;
}

unsigned ProbabilityTheory::factorial(unsigned Number)
{
    if (Number == 1 or Number == 0)
        return 1;
    return Number * factorial(Number - 1);
}

double ProbabilityTheory::localLaplassFunction(double arg)
{
    double value;
    value = (1 / sqrt(PI) * pow(EXP, -1 * pow(arg, 2) / 2));
    return value;
}

unsigned ProbabilityTheory::numberOfCombinations(unsigned NumKits, unsigned NumElements)
{
    return factorial(NumKits) / factorial(NumElements) / factorial(NumKits - NumElements);
}

unsigned ProbabilityTheory::numberOfAccommodations(unsigned NumKits, unsigned NumElements)
{
    return factorial(NumKits) / factorial(NumKits - NumElements);
}

double ProbabilityTheory::getCountInVec(double number, vector<double>& vec)
{
    double count = 0;
    for (size_t idx = 0; idx < vec.size(); idx++)
        if (vec[idx] == number)
            count++;
    return count;
}