#include "BinomialDistribution.h"

BinomialDistribution::BinomialDistribution(double probabiliy, int countOfExperiments)
{
    this->p = probabiliy;
    this->q = 1 - probabiliy;
    this->n = countOfExperiments;
    fillComponentTable();
}

double BinomialDistribution::computeExpectedValue()
{
    return this->n * this->p;
}

double BinomialDistribution::computeDispersion()
{
    return this->n * this->p * this->q;
}

array<vector<double>, 2> BinomialDistribution::fillComponentTable() // p - общеприн€тое обозначение веро€тности (Probability)
{
    for (int k = 0; k <= this->n; k++)
    {
        this->componentTable[0].push_back(k);
        this->componentTable[1].push_back(localLaplassFunction(((k - this->n * this->p) / sqrt(this->n * this->p * this->q))));
        //локальна€ функци€ Ћапласа принимает отношение отклонени€ от матождиани€ к среднему квадр отклонению ((m-M[x])/sqrt(D[x]))
    }
    return this->componentTable;
}

double n, p, q;
array <vector<double>, 2> componentTable;