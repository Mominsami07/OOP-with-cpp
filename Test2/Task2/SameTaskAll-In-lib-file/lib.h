#include <iostream>
#include <string>
#include <vector>

class Work
{
public:
    Work(const std::string &description, const std::string &worker)
        : description_(description), worker_(worker) {}
    virtual ~Work() {}

    std::string getDescription() const { return description_; }
    std::string getWorker() const { return worker_; }
    virtual double getCost() const = 0;

    static int count() { return count_; }

protected:
    std::string description_;
    std::string worker_;
    static int count_;
};
int Work::count_ = 0;

class PieceWork : public Work
{
public:
    PieceWork(const std::string &description, const std::string &worker,
              int pieces, double costPerPiece)
        : Work(description, worker), pieces_(pieces), costPerPiece_(costPerPiece)
    {
        ++count_;
    }
    ~PieceWork() { --count_; }

    int getPieces() const { return pieces_; }
    double getCostPerPiece() const { return costPerPiece_; }

    double getCost() const override { return pieces_ * costPerPiece_; }

private:
    int pieces_;
    double costPerPiece_;
};

class FieldWork : public Work
{
public:
    FieldWork(const std::string &description, const std::string &worker,
              double length, double width, double costPerSquareMeter)
        : Work(description, worker),
          length_(length),
          width_(width),
          costPerSquareMeter_(costPerSquareMeter)
    {
        ++count_;
    }
    ~FieldWork() { --count_; }

    double getLength() const { return length_; }
    double getWidth() const { return width_; }
    double getCostPerSquareMeter() const { return costPerSquareMeter_; }

    double getCost() const override
    {
        return length_ * width_ * costPerSquareMeter_;
    }

private:
    double length_;
    double width_;
    double costPerSquareMeter_;
};

class TimeWork : public Work
{
public:
    TimeWork(const std::string &description, const std::string &worker,
             double hours, double costPerHour)
        : Work(description, worker), hours_(hours), costPerHour_(costPerHour)
    {
        ++count_;
    }
    ~TimeWork() { --count_; }

    double getHours() const { return hours_; }
    double getCostPerHour() const { return costPerHour_; }

    double getCost() const override
    {
        int unpaidHours = hours_ / 9;
        return (hours_ - unpaidHours) * costPerHour_;
    }

private:
    double hours_;
    double costPerHour_;
};

class Schedule
{
public:
    class DeficitError
    {
    public:
        // DeficitError(double deficit) : deficit_(deficit) {}
        DeficitError(std::string info) : info_(info) {}
        double getDeficit() const { return deficit_; }
        // std::string what() const { return "DeficitError"; }
        std::string what() const { return info_; }

    private:
        double deficit_;
        std::string info_;
    };

    class EmptyError
    {
    public:
        std::string what() const { return "EmptyError"; }
    };

    class IndexError
    {
    public:
        std::string what() const { return "IndexError"; }
    };

    Schedule(const std::string &description, double budget)
        : description_(description), budget_(budget) {}
    ~Schedule() {}

    std::string getDescription() const { return description_; }
    double getBudget() const { return budget_; }
    double getRemainingBudget() const { return budget_ - totalCost_; }
    int getNumTasks() const { return tasks_.size(); }
    void clear()
    {
        // iterate through the vector and delete the objects
        // consider that the vector has references to the objects
        // got to each object and delete it
        for (auto task : tasks_)
        {
            delete task;
        }
        tasks_.clear();
    }

    void insert(int pos, Work *task)
    {
        if (pos < 1 || pos > tasks_.size() + 1)
        {
            pos = tasks_.size() + 1;
        }
        if (task->getCost() > getRemainingBudget())
        {
            double temperorr = task->getCost() - getRemainingBudget();
            std::string info = task->getDescription() + " too expensive - only " + std::to_string(getRemainingBudget()) + " free money" + "\n";
            // std::cout << info;
            // std::cout << task->getDescription() << " " << task->getCost() << " " << getRemainingBudget() << std::endl;
            delete task;
            throw DeficitError(info);
        }
        tasks_.insert(tasks_.begin() + pos - 1, task);
        totalCost_ += task->getCost();
    }

    void removeFirst()
    {
        if (tasks_.empty())
        {
            throw EmptyError();
        }
        Work *task = tasks_[0];
        totalCost_ -= tasks_[0]->getCost();
        tasks_.erase(tasks_.begin());
        delete task;
    }

    void removeAll() { tasks_.clear(); }

    double summaryCost() const { return totalCost_; }

    Work &operator[](int pos)
    {
        if (pos < 1 || pos > tasks_.size())
        {
            throw IndexError();
        }
        return *tasks_[pos - 1];
    }

    friend std::ostream &operator<<(std::ostream &out, const Schedule &schedule)
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

private:
    std::string description_;
    double budget_;
    double totalCost_ = 0;
    std::vector<Work *> tasks_;
};