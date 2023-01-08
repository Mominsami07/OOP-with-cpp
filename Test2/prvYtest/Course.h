#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
using namespace std;

class Course
{
protected:
    string name;
    string ScArea;
    static int NumOfCourses;

public:
    Course(string n, string Sc) : name(n), ScArea(Sc)
    {
        NumOfCourses++;
    }

    virtual ~Course()
    {
        NumOfCourses--;
    }

    string getCourseName()
    {
        return name;
    }
    string getSc()
    {
        return ScArea;
    }

    static int count()
    {
        return NumOfCourses;
    }
    virtual double getMark() = 0;
};

int Course::NumOfCourses = 0;

class ScoredCourse : public Course
{
protected:
    int points;

public:
    ScoredCourse(string n, string Sc, int p) : Course(n, Sc), points(p)
    {
    }
    ~ScoredCourse() {}

    double getMark()
    {
        if (0 <= points && points <= 49)
        {
            return 2;
        }
        else if (50 <= points && points <= 59)
        {
            return 3;
        }
        else if (60 <= points && points <= 69)
        {
            return 3.5;
        }
        else if (70 <= points && points <= 79)
        {
            return 4;
        }
        else if (80 <= points && points <= 89)
        {
            return 4.5;
        }
        else
        {
            return 5;
        }
    }
};

class AverageCourse : public Course
{
protected:
    double p1;
    double p2;

public:
    AverageCourse(string n, string Sc, double mark1, double mark2) : Course(n, Sc), p1(mark1), p2(mark2)
    {
    }

    ~AverageCourse() {}

    double getMark()
    {
        if (p1 == 2 || p2 == 2)
        {
            return 2;
        }
        else
        {
            return (p1 + p2) / 2;
        }
    }
};

class CheckCourse : public Course
{
protected:
    bool a1;
    bool a2;
    bool a3;
    bool a4;

public:
    CheckCourse(string n, string Sc, bool as1, bool as2, bool as3, bool as4) : Course(n, Sc), a1(as1), a2(as2), a3(as3), a4(as4)
    {
    }

    ~CheckCourse() {}

    double getMark()
    {
        bool arr[4] = {a1, a2, a3, a4};
        int countPassed = 0;
        for (int i = 0; i < 4; i++)
        {
            if (arr[i])
            {
                countPassed++;
            }
        }
        if (countPassed == 0 || countPassed == 1)
        {
            return 2;
        }
        else if (countPassed == 2)
        {
            return 3;
        }
        else if (countPassed == 3)
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
};

#endif