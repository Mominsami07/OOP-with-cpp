#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "Schedule.h"
#include "Work.h"
using namespace std;

Schedule::Schedule(const string &_description, double _budget)
{
    description_ = _description;
    budget_ = _budget;
    totalCost_ = 0;
}
Schedule::~Schedule()
{
    for (auto task : tasks_)
    {
        delete task;
    }
    tasks_.clear();
}

std::string Schedule::getDescription() const
{
    return description_;
}

double Schedule::getBudget() const
{
    return budget_;
}

double Schedule::getRemainingBudget() const
{
    return budget_ - totalCost_;
}

int Schedule::getNumTasks() const
{
    return tasks_.size();
}

void Schedule::insert(int pos, Work *task)
{
    if (pos < 1 || pos > tasks_.size() + 1)
    {
        pos = tasks_.size() + 1;
    }
    if (task->getCost() > getRemainingBudget())
    {
        double temperorr = task->getCost() - getRemainingBudget();
        ostringstream os;
        os << task->getDescription() << " too expensive - only " << std::to_string(getRemainingBudget()) << " free money";
        string info = os.str();
        // std::string info = task->getDescription() + " too expensive - only " + std::to_string(getRemainingBudget()) + " free money" + "\n";
        // std::cout << info;
        // std::cout << task->getDescription() << " " << task->getCost() << " " << getRemainingBudget() << std::endl;
        delete task;
        throw DeficitError(info);
    }
    tasks_.insert(tasks_.begin() + pos - 1, task);
    totalCost_ += task->getCost();
}

void Schedule::removeAll()
{
    for (auto task : tasks_)
    {
        delete task;
    }
    tasks_.clear();
}

void Schedule::removeFirst()
{
    if (tasks_.empty())
    {
        throw EmptyError("EmptyError");
    }
    else
    {
        Work *task = tasks_[0];
        totalCost_ -= tasks_[0]->getCost();
        tasks_.erase(tasks_.begin());
        delete task;
    }
}

void Schedule::clear()
{
    for (auto task : tasks_)
    {
        delete task;
    }
    tasks_.clear();
}

double Schedule::summaryCost() const
{
    double sum = 0;
    for (auto task : tasks_)
    {
        sum += task->getCost();
    }
    return sum;
}

Work &Schedule::operator[](int pos)
{
    if (pos < 1 || pos > tasks_.size())
    {
        throw IndexError("IndexError");
    }
    else
    {
        return *tasks_[pos - 1];
    }
}

std::ostream &operator<<(std::ostream &out, const Schedule &schedule)
{
    out << schedule.description_ << ", total budget: " << schedule.budget_
        << ", remaining money: " << schedule.getRemainingBudget() << ":\n";
    for (int i = 0; i < schedule.tasks_.size(); ++i)
    {
        out << i + 1 << ". " << schedule.tasks_[i]->getDescription() << " ("
            << schedule.tasks_[i]->getWorker() << "), cost: "
            << schedule.tasks_[i]->getCost() << "\n";
    }
    return out;
}

// Path: Schedule.h
