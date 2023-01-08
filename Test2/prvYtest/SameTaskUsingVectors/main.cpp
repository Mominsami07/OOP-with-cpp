#include <iostream>
#include "Course.h"
#include "Study.h"

using namespace std;

int main()
{

    Study uni("Jhon Smith", 2, 3);   // Max 3 courses
    cout << Course::count() << endl; // 0

    try
    {
        uni.add(new ScoredCourse("Programming", "computers", 65)); // 65 points
        uni.add(new AverageCourse("English", "Languages", 4, 5));
        uni.add(new CheckCourse("Engineering", "computers", true, false, true, true));
        uni.add(new ScoredCourse("Football", "sport", 90)); // 90 points
    }
    catch (Study::LimitedError &e)
    {
        cout << e.what() << endl; // only 3 courses allowed
    }
    cout << uni;
    // Jhon Smith, year 2, average grade: 4 :
    // 1. Programming, area: computers, mark: 3.5
    // 2. English, area: Languages, mark: 4.5
    // 3. Engineering, area: computers, mark: 4
    cout << Course::count() << endl;    // 3
    cout << uni.averageGrade() << endl; // 4.00
    // try
    // {
    //     uni.remove("English");
    //     uni.remove("Math");
    // }
    // catch (Study::NameError &e)
    // {
    //     cout << e.what() << endl;
    // }
    uni.remove("English");
    cout << "After Removing" << endl;
    cout << Course::count() << endl;    // 2
    cout << uni.averageGrade() << endl; // 3.75
    try
    {

        cout << uni[1].getMark() << endl; // 3.5
        cout << uni[5].getMark() << endl; // IndexError
    }
    catch (Study::IndexError &e)
    {
        cout << e.what() << endl;
    }
    uni.clear();
    cout << Course::count() << endl; // 0

    return 0;
}