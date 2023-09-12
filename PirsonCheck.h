#pragma once
#include "ProbabilityTheory.h"
#include<map>
using std::map;
class PirsonCheck : ProbabilityTheory
{
public:
    PirsonCheck(vector<double>& input);
    static vector<double> setSample();
    bool isPirson();
    void getResults();

private:

    double SturgessFormula(vector<double>& input);
    vector<double> getSummedWithH();
    double computeExpectedValue() override;
    double computeDispersion() override;
    vector<double> getCounters();
    vector<double> getCountersInRange();
    vector<double> getDividedCounters();
    vector<double> getLaplassArguments();
    vector<double> getLaplassResults();
    vector<double> getTheoreticalFrequency();
    double get_x_2_q();
    int getDegreesOfFreedom();
    int countInRange(double x1);
    vector<double> equidistant(vector<double>& vec);

    vector <double> sample_;
    map<const char*, vector<double>> rows;
    double h; // обозначение расстояния между равноотстоящими вариантами
    size_t nums_count;
    size_t row_len;
    double expectedValue = 0;
    double dispersion = 0;
    array <vector<double>, 2> componentTable;
};
