#include "Correlation.h"
Correlation::Correlation(array<vector<double>, 2> pairs) : pairs{ pairs }
    {
        this->experimentsCount_ = size(pairs[0]);
        this->componentTableX = getComponentTable(pairs[0]); //Tables of each variable (values and their probabilities)
        this->componentTableY = getComponentTable(pairs[1]);
        this->correlationTable = getCorrelationTable();
        tableCountOfSamePairs();
    }
    map <const char*, double> numberCharacteristics;

    double Correlation::computeTwoDimensionalExpectedValue()
    {
        double expectedValue = 0;
        for (size_t i = 1; i < size(this->correlationTable); i++)
            for (size_t j = 1; j < size(this->correlationTable[0]); j++)
                expectedValue += this->correlationTable[i][0] * this->correlationTable[i][j] * this->correlationTable[0][j];
        return expectedValue / this->experimentsCount_;
    }
    size_t experimentsCount_;
    array<vector<double>, 2> pairs;
    vector<vector <double>> correlationTable;
    array <vector <double>, 2> componentTableX;
    array <vector <double>, 2> componentTableY;
    std::map <std::array<double, 2>, unsigned> countOfEachPair;
    double Correlation::computeExpectedValueComponent(array <vector<double>, 2>& componentTable) //standart expected value formula
    {
        double expectedValue = 0;
        for (size_t i = 0; i < size(this->componentTable[0]); i++)
            expectedValue += this->componentTable[0][i] * this->componentTable[1][i];
        return expectedValue;
    }
    double Correlation::computeDispersionComponent(array <vector<double>, 2>& componentTable)
    {
        double Dispersion = 0;
        for (size_t i = 0; i < size(componentTable[0]); i++)
            Dispersion += pow(componentTable[0][i], 2) * componentTable[1][i];
        Dispersion -= pow(this->computeExpectedValueComponent(componentTable), 2); //D[x] = M[x^2] - M^2{x]
        return Dispersion / this->experimentsCount_;
    }
    void Correlation::fillNumberCharacteristics() //
    {
        this->numberCharacteristics["expectedValueX"] = this->computeExpectedValueComponent(this->componentTableX);
        this->numberCharacteristics["expectedValueY"] = this->computeExpectedValueComponent(this->componentTableY);
        this->numberCharacteristics["dispersionX"] = computeDispersionComponent(this->componentTableX);
        this->numberCharacteristics["dispersionY"] = computeDispersionComponent(this->componentTableY);
        this->numberCharacteristics["expectedValueXandY"] = computeTwoDimensionalExpectedValue();
        this->numberCharacteristics["correlationMoment"] = getCorrelationMoment();
        this->numberCharacteristics["correlationKoefficient"] = getCorrelationKoefficient();
    }
    array <vector<double>, 2> Correlation::getComponentTable(vector<double>& row)
    {
        vector <double> experements = getUniqueAndSort(row);
        vector <double> countEachExperement;
        for (double el : experements)
            countEachExperement.push_back(getCountInVec(el, row));
        return { countEachExperement, experements };
    }
    vector <double> Correlation::getUniqueAndSort(vector<double>& row)
    {
        vector <double> componentTable;
        std::sort(row.begin(), row.end());
        for (size_t i = 1; i < this->experimentsCount_; ++i)
            if (row[i] != row[i - 1])
                componentTable.push_back(row[i - 1]);
        componentTable.push_back(row.back());
        return componentTable;
    }

    void Correlation::tableCountOfSamePairs()
    {
        for (size_t i = 0; i < size(this->pairs[0]); i++)
            this->countOfEachPair[{pairs[0][i], pairs[1][i]}]++;
    }

    vector <vector <double>> Correlation::getCorrelationTable()
    {
        vector <vector <double>> correlationTable; correlationTable[0].push_back(NULL);
        correlationTable.push_back(this->componentTableX[0]);
        for (size_t i = 0; i < size(this->componentTableY[0]); i++)
            correlationTable[i + 1].push_back(this->componentTableY[0][i]);
        for (size_t i = 1; i <= size(this->componentTableY[1]); i++)
            for (size_t j = 1; j <= size(this->componentTableX[1]); j++)
                correlationTable[i].push_back(this->countOfEachPair[{this->componentTableX[1][j - 1], this->componentTableY[1][i - 1]}]);
        return correlationTable;
    }

    double Correlation::getCorrelationMoment()
    {
        return this->numberCharacteristics["expectedValueXandY"] - this->numberCharacteristics["expectedValueX"]
            * this->numberCharacteristics["expectedValueY"];
    }

    bool Correlation::isCorrelate()
    {
        return this->numberCharacteristics["correlationMoment"]; //if correletion moment is zero, there is no correlation
    }

    double Correlation::getCorrelationKoefficient()
    {
        return sqrt(pow(this->numberCharacteristics["correlationMoment"], 2) /
            (this->numberCharacteristics["dispersionX"] * this->numberCharacteristics["dispersionY"]));
    }

    void Correlation::strenghtOfCorrelation() //as more correlation koefficient as stronger coorelation is
    {
        if (this->numberCharacteristics["correlationKoefficient"] > 0.7)
        {
            cout << " correlation is strong\n"; makeLineRegression();
        }
        else if (this->numberCharacteristics["correlationKoefficient"] >= 0.3)
        {
            cout << " correlation is middle\n";  makeLineRegression();
        }
        else
            cout << " correlation is weak \n"; //if correlation is weak it makes no sense to make line of regression
    }
    void Correlation::makeLineRegression()
    {
        //...
    }