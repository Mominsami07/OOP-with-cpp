
#include "lib.h"

#include <iostream>

using namespace std;

int main()
{
    Product p1("HP DeskJet 3110 printer");
    cout<< p1.getName() <<", ID: " << p1.getID() <<endl;
    p1.addOrder("Warsaw",20);
    p1.addOrder("Gdansk",30);
    p1.addOrder("Warsaw",20);
    //p1.deleteDestination("Gdansk");
    cout<<p1.numberOfDest() << endl;
    cout<<p1.greatestOrderDest()<<endl;
    p1[2]="Lodz";
    cout<<p1;
    return 0;
}
