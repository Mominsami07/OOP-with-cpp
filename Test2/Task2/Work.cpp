#include "Work.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Work::count_ = 0;

Work::Work(const std::string &description, const std::string &worker)
{
    description_ = description;
    worker_ = worker;
}

Work::~Work()
{
}

std::string Work::getDescription() const
{
    return description_;
}

std::string Work::getWorker() const
{
    return worker_;
}

int Work::count()
{
    return count_;
}

PieceWork::PieceWork(const std::string &description, const std::string &worker,
                     int pieces, double costPerPiece)
    : Work(description, worker), pieces_(pieces), costPerPiece_(costPerPiece)
{
    ++count_;
}

PieceWork::~PieceWork()
{
    --count_;
}

int PieceWork::getPieces() const
{
    return pieces_;
}

double PieceWork::getCostPerPiece() const
{
    return costPerPiece_;
}

double PieceWork::getCost() const
{
    return pieces_ * costPerPiece_;
}

FieldWork::FieldWork(const std::string &description, const std::string &worker,
                     double length, double width, double costPerSquareMeter)
    : Work(description, worker),
      length_(length),
      width_(width),
      costPerSquareMeter_(costPerSquareMeter)
{
    ++count_;
}

FieldWork::~FieldWork()
{
    --count_;
}

double FieldWork::getLength() const
{
    return length_;
}

double FieldWork::getWidth() const
{
    return width_;
}

double FieldWork::getCostPerSquareMeter() const
{
    return costPerSquareMeter_;
}

double FieldWork::getCost() const
{
    return length_ * width_ * costPerSquareMeter_;
}

TimeWork::TimeWork(const std::string &description, const std::string &worker,
                   double hours, double costPerHour)
    : Work(description, worker), hours_(hours), costPerHour_(costPerHour)
{
    ++count_;
}

TimeWork::~TimeWork()
{
    --count_;
}

double TimeWork::getHours() const
{
    return hours_;
}

double TimeWork::getCostPerHour() const
{
    return costPerHour_;
}

double TimeWork::getCost() const
{
    int unpaidHours = hours_ / 9;
    return (hours_ - unpaidHours) * costPerHour_;
}
