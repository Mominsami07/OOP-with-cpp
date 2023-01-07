#ifndef LIB_H
#define LIB_H
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

class Case
{
private:
    string label;
    int colour;
    static int numCases;

public:
    Case(string label, int colour) : label(label), colour(colour) { numCases++; }
    virtual ~Case() { numCases--; }

    string getLabel() const { return label; }
    void setLabel(string label) { this->label = label; }

    int getColour() const { return colour; }
    void setColour(int colour) { this->colour = colour; }

    virtual double getCapacity() const = 0;

    static int count() { return numCases; }
};

int Case::numCases = 0;

class BrickCase : public Case
{
public:
    BrickCase(string label, int colour, double length, double width, double height)
        : Case(label, colour), length(length), width(width), height(height) {}

    double getLength() const { return length; }
    void setLength(double length) { this->length = length; }

    double getWidth() const { return width; }
    void setWidth(double width) { this->width = width; }

    double getHeight() const { return height; }
    void setHeight(double height) { this->height = height; }

    double getCapacity() const override { return length * width * height; }

private:
    double length;
    double width;
    double height;
};

class TubeCase : public Case
{
public:
    TubeCase(string label, int colour, double radius, double height)
        : Case(label, colour), radius(radius), height(height) {}

    double getRadius() const { return radius; }
    void setRadius(double radius) { this->radius = radius; }

    double getHeight() const { return height; }
    void setHeight(double height) { this->height = height; }

    double getCapacity() const override { return 3.14 * radius * radius * height; }

private:
    double radius;
    double height;
};

class PrismCase : public Case
{
public:
    PrismCase(string label, int colour, double base, double height)
        : Case(label, colour), base(base), height(height) {}

    double getBase() const { return base; }
    void setBase(double base) { this->base = base; }

    double getHeight() const { return height; }
    void setHeight(double height) { this->height = height; }

    double getCapacity() const override
    {
        return (base * base * sqrt(3)) / 4 * height;
    }

private:
    double base;
    double height;
};

class Repository
{
private:
    double available;
    string description;
    double capacity;
    double leftcapacity;
    vector<Case *> cases;

public:
    class NameError : public runtime_error
    {
    public:
        NameError() : runtime_error("NameError: case not found.") {}
    };

    class IndexError : public runtime_error
    {
    public:
        IndexError() : runtime_error("IndexError: index out of range.") {}
    };
    class CapacityError : public runtime_error
    {
    public:
        CapacityError(double available, double required)
            : runtime_error(""), available(available), required(required) {}
        const char *what() const noexcept override
        {
            return ("CapacityError: " + to_string(required) +
                    " required, but only " + to_string(available) + " available.")
                .c_str();
        }
        // string what() const noexcept override
        // {
        //     return "CapacityError: " + to_string(required) +
        //            " required, but only " + to_string(available) + " available.";
        // }
        double available;
        double required;
    };

    Repository(string description, double capacity)
        : description(description), capacity(capacity), leftcapacity(capacity) {}

    ~Repository()
    {
        clear();
    }

    void add(Case *c)
    {
        if (leftcapacity - c->getCapacity() >= 0)
        {
            leftcapacity -= c->getCapacity();
            cases.push_back(c);
        }
        else
        {
            double objCapacity = c->getCapacity();
            delete c;
            throw CapacityError(leftcapacity, objCapacity);
        }
    }

    void remove(string label)
    {
        for (auto it = cases.begin(); it != cases.end(); it++)
        {
            if ((*it)->getLabel() == label)
            {
                leftcapacity += (*it)->getCapacity();
                delete *it;
                cases.erase(it);
                return;
            }
        }
        throw NameError();
    }

    void clear()
    {
        for (Case *c : cases)
        {
            delete c;
        }
        cases.resize(0);
        leftcapacity = 100;
    }

    double summaryVolume() const
    {
        double totalVolume = 0;
        for (Case *c : cases)
        {
            totalVolume += c->getCapacity();
        }
        return totalVolume;
    }

    const Case &operator[](int index) const
    {
        if (index >= cases.size())
        {
            throw IndexError();
        }

        return *cases[index];
    }

    friend ostream &operator<<(ostream &os, const Repository &repo)
    {
        os << repo.description << ", total capacity: " << repo.capacity << ", free space: "
           << repo.capacity - repo.summaryVolume() << ":" << endl;
        for (int i = 0; i < repo.cases.size(); i++)
        {
            os << i + 1 << ". " << repo.cases[i]->getLabel() << ", 0x" << hex
               << repo.cases[i]->getColour() << dec << ", volume: "
               << repo.cases[i]->getCapacity() << endl;
        }
        return os;
    }
};

#endif