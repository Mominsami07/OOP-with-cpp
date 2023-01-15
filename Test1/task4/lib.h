#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class CarData
{
private:
    string regNumber;
    string carBrand;
    vector <string> customerNames;
    vector <int> periods;
    static int RentalsCounter;

public:
    CarData(string cReg =" ", string cBrand=" ")
    {
        regNumber =cReg;
        carBrand = cBrand;
    }
    ~CarData()
    {
        cout << regNumber << " Has been destroyed ! "<<endl;
    }

    //copy constructor

    CarData(const CarData &x)
    {

        regNumber= x.regNumber;
        carBrand= x.carBrand;
        if(!x.customerNames.empty())
        {
            customerNames=x.customerNames;
        }
        if(!x.periods.empty())
        {
            periods=x.periods;
        }
        // might need to increase the Rentals counter
    }
// assignment operator

    CarData &operator =(const CarData &other)
    {

        regNumber = other.regNumber;
        carBrand=other.carBrand;
        customerNames=other.customerNames;
        periods=other.periods;
        //might need to take care of the Rentals counter

        return *this;
    }

    // setters

    void setRegistrationNumber(string regNum)
    {
        regNumber = regNum;
    }
// getters
    string getRegistrationNumber()
    {
        return regNumber;
    }
    string getBrand()
    {

        return carBrand;
    }

    void addRentals(string custName, int rentalPeriod)
    {
        customerNames.push_back(custName);
        periods.push_back(rentalPeriod);
        RentalsCounter++;
    }

    // remove Rentals method
    void removeRentals(string custName)
    {

        bool found= false;

        for(int i=0; i<customerNames.size(); i++)
        {
            if(customerNames[i]==custName)
            {
                found=true;
                customerNames.erase(customerNames.begin()+i);
                periods.erase(periods.begin()+i);
            }
        }

        if(!found)
        {
            throw logic_error ("customer  does not exist! ");
        }

    }

// average time method

    double averageTime()
    {
        int sum=0;
        for(int i=0; i<periods.size(); i++)
        {
            sum+=periods[i];
        }
        return (double)sum/periods.size();
    }

    // getRentalsCount method

    static int getRentalsCount()
    {
        return RentalsCounter;
    }

    // indexing operator

    int &operator [](int position)
    {
        if(position<=0 || position > periods.size())
        {
            throw logic_error ( " position does not exist");
        }
        return periods[position-1];
    }
    // shift operator

    friend ostream &operator << (ostream &out, const CarData &x)
    {
        out<< "car : " << x.carBrand << "  "<< x.regNumber << endl;
        int sum=0;
        for(int i=0; i < x.customerNames.size(); i++)
        {
            out<< i+1 <<". " << x.customerNames[i] << ", "<< x.periods[i] <<endl;
            sum+=x.periods[i];
        }

        out << "Total time: " << sum << " hours"<< endl;
        return out;
    }
// smaller than operator

bool operator < (const CarData &x)
{

    return periods.size() < x.periods.size();
}
};

int CarData::RentalsCounter=0;
#endif
