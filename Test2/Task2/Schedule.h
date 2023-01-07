#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Work.h"
using namespace std;

class Schedule
{
private:
    std::string description_;
    double budget_;
    double totalCost_ = 0;
    std::vector<Work *> tasks_;

public:
    class DeficitError : public logic_error
    {
    public:
        DeficitError(string msg = "sth wrong") : logic_error(msg) {}
    };

    class EmptyError : public logic_error
    {
    public:
        EmptyError(string msg) : logic_error(msg) {}
    };

    class IndexError : public out_of_range
    {
    public:
        IndexError(string msg) : out_of_range(msg) {}
    };

    Schedule(const std::string &description, double budget);
    virtual ~Schedule();
    std::string getDescription() const;
    double getBudget() const;
    double getRemainingBudget() const;
    int getNumTasks() const;
    void insert(int pos, Work *task);
    void removeAll();
    void removeFirst();
    double summaryCost() const;
    void clear();
    Work &operator[](int pos);
    friend std::ostream &operator<<(std::ostream &out, const Schedule &schedule);
};

#endif // SCHEDULE_H