#include <iostream>
#include "lib.h"
using namespace std;

int main()
{
    cout << CarData::getRentalsCount()<<endl; //should be 0
    CarData c1("EL12345", "Toyota Yaris");
    cout << c1.getRegistrationNumber() << endl; //should be EL12345
    c1.addRentals("John Smith", 7);
    c1.addRentals("Jonathan Taylor", 10);
    cout << c1.averageTime()<<endl; //should be 8.5
    c1[1] = 12; //changes the period of the first rental
    cout << c1;
    //car: Toyota Yaris EL12345
//1. John Smith, 12
//2. Jonathan Taylor, 10
//Total time: 22 hours

    CarData c2("EL12233", "Opel Astra");
    c2.addRentals("Mark Johnson", 10);
    c2.addRentals("Elizabeth Smith", 3);
    c2.addRentals("Mark Johnson", 2);
    if (c1 < c2)
cout << c1.getBrand() << " is used less often that " << c2.getBrand() << endl;
    c2.removeRentals("Mark Johnson");

    cout << c2;
    //car: Opel Astra EL12233
//1. Elizabeth Smith, 3
//Total time: 12 hours // considering the flow and the logic of th  program this should be 3 not 12
    cout << CarData::getRentalsCount()<<endl; //should be 5
    return 0;
}
