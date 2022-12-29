#include <iostream>
#include "lib.h"
#include "lib.cpp"
using namespace std;

int main()
{
    cout << "Over time workers: " << Worker::overTimeWorkers() << endl;
    Worker s;
    Worker w1("Jhon Smith", 20.0);
    cout << w1.getName() << ", per hour: " << w1.getWage() << endl;
    w1.addTime(4);
    w1.addTime(18);
    w1.addTime(10);
    cout << "List Size: " << w1.listSize() << endl;
    w1[3] = 15;
    w1.modifyTimes();
    cout << w1;
    cout << "List Size: " << w1.listSize() << endl;

    Worker w2(w1);

    w2.setName("Andrew Taylor");
    w2.setWage(22.5);
    w2.addTime(24);
    w2.addTime(24);
    w2.addTime(24);
    w2.addTime(24);
    w2.addTime(24);
    w2.addTime(24);
    w2.addTime(18);
    cout << "wage for w2: " << w2.getWage() << endl; // testing
    cout << "Total work time for W2: " << w2.totalWorktime() << endl;
    cout << w2; // testing
    cout << "Earnings for w2: " << w2.getEarnings() << endl;
    cout << "Sum of all worked time: " << Worker::totalWorktime() << endl;

    if (w2 > w1)
    {
        cout << w2.getName() << " worked longer than " << w1.getName() << endl;
    }

    cout << Worker::overTimeWorkers() << endl;
    return 0;
}