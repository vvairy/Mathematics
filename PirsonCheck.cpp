#include "PirsonCheck.h"
PirsonCheck::PirsonCheck(vector<double>& input) : sample_(input)
{
    this->nums_count = size(input);
    this->rows["validated"] = this->equidistant(input);
    this->h = this->SturgessFormula(input);
    isPirson();
}
vector<double> PirsonCheck::setSample()
{
    unsigned nums_count;
    std::cout << "Enter nums count: ";
    std::cin >> nums_count;
    std::cout << "Enter nums:\n";

    vector <double> input_data(nums_count); double number; unsigned i = 0;
   
    while (i < nums_count)
    {
        cout << ++i << ". ";

        while (!(std::cin >> number)) { // checking success of reading input
            std::cout << "Incorrect input. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip remaining part of string
        }

        input_data.push_back(number);
    }

    return input_data;
}

bool PirsonCheck::isPirson()
{
    cout << "Do some magic: \n h = " << this->h << endl;
    this->rows["counters"] = this->getCounters();
    this->rows["counters_in_range"] = this->getCountersInRange();
    this->rows["summed_with_h"] = this->getSummedWithH();
    this->row_len = size(getSummedWithH());
    this->rows["divided_counters"] = this->getDividedCounters();
    this->componentTable[0] = this->rows["summed_with_h"]; this->componentTable[1] = this->rows["counters_in_range"];

    computeExpectedValue(); computeDispersion();

    double s_2 = (double(this->nums_count) / double(this->nums_count - 1)) * this->dispersion;
    double s = sqrt(s_2);

    this->rows["laplass_arguments"] = this->getLaplassArguments();
    this->rows["laplass_results"] = this->getLaplassResults();
    this->rows["theoretical_frequency"] = this->getTheoreticalFrequency();

    double x_2_q = this->get_x_2_q();
    int degreesOfFreedom = this->getDegreesOfFreedom();

    return x_2_q - degreesOfFreedom * 1.2 >= 2.3; //условие соответсвия нормальному Закону Распредeления
}

void PirsonCheck::getResults()
{
    for (auto it = rows.begin(); it != rows.end(); ++it)
    {
        cout << it->first << endl;
        for (size_t i = 0; i < (it->second.size()); ++i)
        {
            cout << " " << it->second[i];
        }
        cout << endl;
    }
    cout << "Supporting Value = " << get_x_2_q() << "\nCount degrees of Freedoms = " << getDegreesOfFreedom()
        << "\nexpectedValue = " << this->expectedValue << "\nDispersion = " << this->dispersion
        << "\nAverage Square Deviation = " << sqrt(this->dispersion) << endl;
    if (isPirson())
        std::cout << "Selection corresponds to Normal Law Of Distribution\n";
    else
        std::cout << "Selection doesn't correspond to Normal Law Of Distribution\n";
}

double PirsonCheck::SturgessFormula(vector<double>& input)
{
    return (this->rows["validated"].back() - this->rows["validated"][0]) / (1 + 3.32 * log10(size(input)));//находим шаг равноотстоящей выборки
}

vector<double> PirsonCheck::getSummedWithH()
{
    vector<double> summedWithH;
    double xMin = this->rows["validated"][0], xMax = this->rows["validated"].back();
    while (xMin < xMax)
    {
        summedWithH.push_back(xMin);
        xMin += this->h;
    }
    summedWithH.push_back(xMin);
    return summedWithH;
}

double PirsonCheck::computeExpectedValue()
{
    for (size_t i = 0; i < size(this->componentTable[0]); ++i)
        this->expectedValue += this->componentTable[0][i] * this->componentTable[1][i];
    return this->expectedValue /= this->nums_count;
}
double PirsonCheck::computeDispersion()
{
    for (size_t i = 0; i < size(this->componentTable[0]); ++i)
        this->dispersion += pow(this->componentTable[0][i], 2) * this->componentTable[1][i];
    this->dispersion /= size(this->componentTable[0]); this->dispersion -= pow(this->expectedValue, 2);
    return this->dispersion;
}

vector<double> PirsonCheck::getCounters()
{
    vector <double> counters;
    for (size_t idx = 0; idx < this->rows["validated"].size(); idx++)
    {
        counters.push_back(getCountInVec(this->rows["validated"][idx], this->sample_));
    }
    return counters;
}

vector<double> PirsonCheck::getCountersInRange()
{
    double xMin = this->rows["validated"][0], xMax = this->rows["validated"].back();
    vector<double> counters;
    while (xMin < xMax)
    {
        counters.push_back(this->countInRange(xMin));
        xMin += this->h;
    }
    counters.push_back(this->countInRange(xMin));
    return counters;
}

vector<double> PirsonCheck::getDividedCounters()
{
    vector<double> dividedCounters(this->row_len);
    for (int idx = 0; idx < this->row_len; idx++)
        dividedCounters[idx] = this->rows["counters_in_range"][idx] / this->nums_count;
    return dividedCounters;
}

vector<double> PirsonCheck::getLaplassArguments()
{
    vector<double> laplassArguments(this->row_len);
    for (size_t idx = 0; idx < this->row_len; idx++)
        laplassArguments[idx] = (this->rows["summed_with_h"][idx] - this->expectedValue) / sqrt(this->dispersion);
    return laplassArguments;
}

vector<double> PirsonCheck::getLaplassResults()
{
    vector<double> laplassResults(this->row_len);
    for (size_t idx = 0; idx < this->row_len; idx++)
        laplassResults[idx] = localLaplassFunction(this->rows["laplass_arguments"][idx]);
    return laplassResults;
}

vector<double> PirsonCheck::getTheoreticalFrequency()
{
    vector<double> theoreticalFrequency;
    for (size_t idx = 0; idx < this->row_len; idx++)
        theoreticalFrequency.push_back((this->nums_count * this->h) / sqrt(this->dispersion) * this->rows["laplass_results"][idx]);
    return theoreticalFrequency;
}

double PirsonCheck::get_x_2_q()
{
    double x_2_q = 0;
    for (size_t idx = 0; idx < this->row_len; idx++)
        x_2_q += pow(this->rows["counters_in_range"][idx] - this->rows["theoretical_frequency"][idx], 2) / this->rows["theoretical_frequency"][idx];
    return x_2_q;
}

int PirsonCheck::getDegreesOfFreedom()
{
    return this->row_len - 3;
}

int PirsonCheck::countInRange(double x1)
{
    int counter = 0;
    for (int i = 0; i < size(this->sample_); i++)
    {
        if (x1 - this->h / 2 <= this->sample_[i] && this->sample_[i] < x1 + this->h / 2)
            counter++;
    }
    return counter;
}

vector<double> PirsonCheck::equidistant(vector<double>& vec)
{
    vector<double> res;
    sort(vec.begin(), vec.end());
    for (size_t i = 1; i < size(vec); i++)
        if (vec[i] != vec[i - 1])
            res.push_back(vec[i - 1]);
    res.push_back(vec.back());
    return res;
}