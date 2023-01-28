#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include<string>
#include <limits.h>
using namespace std;

class Product
{
private:
    string name;
    int id;
    static int counter;
    vector <string> destinations;
    vector <int> amount;
    static int total;

public:
    Product(string n=" ")
    {
        name = n;
        counter++;
        id=counter;
    }
    ~Product()
    {
        cout<< name << " Has been destroyed!"<<endl;
    }
    // copy constructor
    Product(const Product &x)
    {
        name=x.name;
        if(x.destinations.size()!=0)
        {
            destinations = x.destinations;
        }
        if(x.amount.size()!=0)
        {
            amount = x.amount;
        }
        for (int i = 0; i < x.amount.size(); i++)
        {
            total += x.amount[i];
        }
        counter++;
        id=counter;
    }

    // assignment
    Product &operator =(const Product &other)
    {
        int sum;
        for(int i=0; i <amount.size();i++){
            total-=amount[i];
        }
        name = other.name;

        destinations = other.destinations;

        amount = other.amount;
        for(int i=0;i<other.amount.size();i++){
            total+=other.amount[i];
        }

        return *this;
    }

// setters

    void setName(string n)
    {
        name =n;
    }
    string getName ()
    {

        return name;
    }

    int getID()
    {
        return id;
    }


    // addOrder

    void addOrder(string dest, int amou)
    {

        bool found = false;

        for(int i=0; i<destinations.size(); i++)
        {
            if(destinations[i] == dest)
            {
                amount[i] += amou;
                found=true;
            }
        }

        if(!found)
        {
            destinations.push_back(dest);
            amount.push_back(amou);
        }
        total += amou;
    }

//deleteDestination method
    void deleteDestination(string dest)
    {
        bool found = false;

        for(int i=0; i<destinations.size(); i++)
        {
            if(destinations[i] == dest)
            {

                destinations.erase(destinations.begin()+i);
                amount.erase(amount.begin()+i);
                total-=amount[i];
                found=true;
            }
        }
        if(!found)
        {
            throw logic_error (" Destination not found");
        }

    }

    // NumberOfDest

    int numberOfDest()
    {

        return destinations.size();
    }

    // greatest order destinaton

    string greatestOrderDest()
    {
        int maxAmount = -1;
        int index=-1;

        for(int i=0; i<amount.size(); i++)
        {

            if(amount[i]>maxAmount)
            {
                maxAmount =amount[i];
                index=i;
            }
        }
        return destinations[index];
    }

    // indexing operator

    string &operator[] (int position){
        if(position <=0  || position > destinations.size())
        {
            throw logic_error ("position does not exist");
        }

        return destinations[position-1];
    }

    // shift operators

    friend ostream &operator <<(ostream &out, const Product &x){
        int total=0;
        int maxAmount = -1;
        int index=-1;
        cout << "Delivery list for : "<< x.name<< " ID "<<x.id <<endl;

        for(int i=0; i<x.destinations.size();i++){
            cout<< i+1 <<". " << x.destinations[i] << " - "<< x.amount[i]<<endl;
            total+= x.amount[i];
             if(x.amount[i]>maxAmount)
            {
                maxAmount =x.amount[i];
                index=i;
            }
        }
        cout<< "Total: "<< total << " average: "<< (double)total/x.amount.size()<< " max : " << maxAmount <<" to "<< x.destinations[index]  << endl;
        return out;

    }

    // total amount

    static int totalAmount()  {

        return total;

    }



};

int Product::counter=0;
int Product::total=0;

#endif
