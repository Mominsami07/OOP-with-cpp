#ifndef STUDY_H
#define STUDY_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Course.h"
using namespace std;
class Study
{
protected:
    string studentName;
    int yearOfStudy;
    int MaxCourses;
    vector<Course *> courses;

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

    void remove(string cName)
    {
        bool found = false;

        for (int i = 0; i < courses.size(); i++)
        {
            if (courses[i]->getCourseName() == cName)
            {
                found = true;
                delete courses[i];
                courses.erase(courses.begin() + i);
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

        return *courses[pos - 1];
    }
};

#endif