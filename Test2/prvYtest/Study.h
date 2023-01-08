#ifndef STUDY_H
#define STUDY_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <list>
#include <algorithm>
#include "Course.h"
using namespace std;
class Study
{
protected:
    string studentName;
    int yearOfStudy;
    int MaxCourses;
    list<Course *> courses;

public:
    class LimitedError : public runtime_error
    {

    public:
        LimitedError(string msg = "sth wrong") : runtime_error(msg) {}
    };
    class NameError : public runtime_error
    {

    public:
        NameError(string msg = "sth wrong") : runtime_error(msg) {}
    };
    class IndexError : public runtime_error
    {

    public:
        IndexError(string msg = "sth wrong") : runtime_error(msg) {}
    };

    Study(string stName, int yOfStudy, int mxC) : studentName(stName), yearOfStudy(yOfStudy), MaxCourses(mxC)
    {
    }

    ~Study()
    {
        clear();
    }

    void add(Course *c)
    {
        if (courses.size() == MaxCourses)
        {
            string info = "only " + std::to_string(MaxCourses) + " courses allowed";
            delete c;
            throw LimitedError(info);
        }
        else
        {
            courses.push_back(c);
        }
    }
    void clear()
    {
        for (auto c : courses)
        {
            delete c;
        }
        courses.clear();
    }

    double averageGrade()
    {
        double sum = 0;
        for (auto c : courses)
        {
            sum += c->getMark();
        }
        return sum / Course::count();
    }

    friend ostream &operator<<(ostream &out, const Study &st)
    {
        double sum = 0;
        for (auto c : st.courses)
        {
            sum += c->getMark();
        }
        out << st.studentName << ", "
            << "year " << st.yearOfStudy << ", "
            << "average grade: " << sum / Course::count() << " :" << endl;

        int i = 0;
        for (auto c : st.courses)
        {
            out << i + 1 << ". " << c->getCourseName() << ", area: " << c->getSc() << ", mark: " << c->getMark() << endl;
            i++;
        }
        return out;
    }

    // remove function using Algorithms

    // void remove(string cName)
    // {
    //     bool found = false;
    //     auto it = find_if(courses.begin(), courses.end(),
    //                       [&](const auto &c)
    //                       { return c->getCourseName() == cName; });
    //     if (it != courses.end())
    //     {
    //         found = true;
    //         courses.erase(it);
    //         delete *it;
    //     }
    //     if (!found)
    //     {
    //         string info = cName + " does not exist!";
    //         throw NameError(info);
    //     }
    // }

    // remove function using iteration over list.
    void remove(string cName)
    {
        bool found = false;
        for (auto it = courses.begin(); it != courses.end(); it++)
        {
            if ((*it)->getCourseName() == cName)
            {
                found = true;
                delete *it;
                courses.erase(it);
                break;
            }
        }

        if (!found)
        {
            string info = cName + " does not exist!";
            throw NameError(info);
        }
    }

    Course &operator[](int pos)
    {
        if (pos < 1 || pos > courses.size())
        {
            string info = "item no. " + to_string(pos) + " not found";
            throw IndexError(info);
        }
        auto it = courses.begin();
        std::advance(it, pos - 1);
        return **it;
    }
};

#endif