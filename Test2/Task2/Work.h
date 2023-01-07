#ifndef WORK_H
#define WORK_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;
class Work
{
public:
    Work(const std::string &description, const std::string &worker);
    virtual ~Work();

    std::string getDescription() const;
    std::string getWorker() const;
    virtual double getCost() const = 0;

    static int count();

protected:
    std::string description_;
    std::string worker_;
    static int count_;
};

class PieceWork : public Work
{
public:
    PieceWork(const std::string &description, const std::string &worker,
              int pieces, double costPerPiece);
    ~PieceWork();

    int getPieces() const;
    double getCostPerPiece() const;

    double getCost() const;

private:
    int pieces_;
    double costPerPiece_;
};

class FieldWork : public Work
{
public:
    FieldWork(const std::string &description, const std::string &worker,
              double length, double width, double costPerSquareMeter);
    ~FieldWork();

    double getLength() const;
    double getWidth() const;
    double getCostPerSquareMeter() const;

    double getCost() const;

private:
    double length_;
    double width_;
    double costPerSquareMeter_;
};

class TimeWork : public Work
{
public:
    TimeWork(const std::string &description, const std::string &worker,
             double hours, double costPerHour);
    ~TimeWork();
    double getHours() const;
    double getCostPerHour() const;

    double getCost() const;

private:
    double hours_;
    double costPerHour_;
};

#endif // WORK_H
