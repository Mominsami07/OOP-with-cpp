#include <iostream>
#include "lib.h"
using namespace std;

int main()
{
    cout<< CardStatement::totalSuccOps()<<endl;
    CardStatement c1(200);
    cout<<c1.getNumber()<<endl;
    c1.addOperation("Empik Beekstore",120);
    c1.addOperation("Computers 4U",90);
    c1.addOperation("Bistor Vege",40);
    c1[1]="Empik Bookstore";
    cout<<c1;
    CardStatement c2(100);
    c2.addOperation("ABC Bakery",10);
    c2.addOperation("ALDi",10);
    c2.addOperation("Lidl",300);

    if(c2>c1){
        cout<<"more at: "<<c2.getNumber()<<endl;
    }
    c2.delUnsuccesful();
    c2.increaseLimit(150);
    cout<< c2;


    return 0;
}
