#include "lib.h"
#include <iostream>
using namespace std;
int
    Worker::ov_count = 0;

// default
Worker::Worker(string new_name, float hw)
{
    name = new_name;
    hourly_wage = hw;
}

// destructor

Worker::~Worker()
{
    if (!time_periods.empty())
        time_periods.clear(); // we can forget about clearing vector because it is automaticly dealocatied
}

// copy constructor

Worker::Worker(const Worker &other)
{
    name = other.name;
    hourly_wage = other.hourly_wage;
    if (!time_periods.empty())
        time_periods = other.time_periods;
}

// Assignment operator

Worker &Worker::operator=(const Worker &other) // we put the first referunce to avoid problems for such
                                               // thing { w1=w2=w3}
{
    if (this != &other)
    {
        name = other.name;
        hourly_wage = other.hourly_wage;
        if (!time_periods.empty())
            time_periods.clear();
        else
        {
            time_periods = other.time_periods;
        }
    }

    return *this;
}

// Setters

void Worker::setName(string new_name)
{
    for (int i = 0; i < new_name.length(); i++)
    {
        if (new_name[i] != ' ' && !isalpha(new_name[i]))
            throw logic_error("incorrect name");
    }
    name = new_name;
}

void Worker::setWage(float new_hw)
{
    hourly_wage = new_hw;
}

// Getters

string Worker::getName() const
{
    return name;
}

float Worker::getWage() const
{
    return hourly_wage;
}

int
    Worker::tT = 0;

// Add Time Method

void Worker::addTime(int hw)
{
    int num = 0;
    if (hw > 24 || hw < 0)
    {
        throw runtime_error("it should be as max 24");
    }

    for (int i = 0; i < time_periods.size(); i++)
    {
        num += time_periods[i];
    }

    time_periods.push_back(hw);
    tT += hw;
    if (num < 160 && num + hw > 160)
    {
        ov_count++;
    }
}

// Modify Times Method

void Worker::modifyTimes()
{
    int num = 0;
    for (int i = 0; i < time_periods.size(); i++)
    {
        if (time_periods[i] > 12)
        {
            num = time_periods[i] - 12;
            time_periods.push_back(num);
            time_periods[i] -= num;
            num = 0;
        }
    }
}

// list size Method

int Worker::listSize()
{
    return time_periods.size();
}

// Total work time

int Worker::totalWorktime()
{

    return tT;
}

// index operator

int &Worker::operator[](int n)
{
    if (n <= 0 || n > time_periods.size())
        throw logic_error("incorrect position");
    return time_periods[n - 1];
}

// shift operator

ostream &operator<<(ostream &os, const Worker &other)
{
    int
        total = 0;
    os << "Name:          " << other.name << endl;
    os << "work periods: ";
    for (int i = 0; i < other.time_periods.size(); i++)
    {
        os << other.time_periods[i] << " ";
        total += other.time_periods[i];
    }
    os << ", total time: " << total << endl;
    if (total > 160)
    {
        int rest = total - 160;
        os << "Ernings: " << 160 * other.hourly_wage + (rest * other.hourly_wage * 1.1) << endl;
    }
    else
        os << "Ernings: " << total * other.hourly_wage << endl;
    return os;
}

// Get Earnings Method

float Worker::getEarnings()
{
    float num = 0.0;
    if (totalt() > 160)
    {
        int rest = totalt() - 160;
        num = 160 * hourly_wage + (rest * hourly_wage * 1.1);
    }
    else
        num = totalt() * hourly_wage;
    return num;
}

// Over Time Workers Method

int Worker::overTimeWorkers()
{

    return ov_count;
}

int Worker::totalt() const
{
    int sum = 0;
    for (int i = 0; i < time_periods.size(); i++)
    {
        sum += time_periods[i];
    }
    return sum;
}

bool Worker::operator>(const Worker &w)
{
    return totalt() > w.totalt();
}
