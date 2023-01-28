#ifndef LIB_H
#define LIB_H

#include <iostream>

#include <string>
#include<vector>
#include <stdexcept>
using namespace std;


class CardStatement
{
private:
    int cardNumber;
    static int counter;
    double spenedLimit;
    vector <string> operationDescription;
    vector<double> prices;
    double remaningMoney;
    static int totalSOps;


public:
    CardStatement(double cardLimit )
    {
        spenedLimit = cardLimit;
        remaningMoney=cardLimit;
        counter++;
        if(counter <=9999)
        {
            cardNumber=counter;
        }
    }

    //copy constructor

    CardStatement(const CardStatement &other)
    {

        spenedLimit = other.spenedLimit;
        if(!other.operationDescription.empty())
        {
            operationDescription=other.operationDescription;
        }
        if(!other.prices.empty())
        {
            prices=other.prices;
        }
        counter++;
        if(counter <= 9999)
        {
            cardNumber=counter;
        }
    }

    // assignment operator

    CardStatement &operator = (const CardStatement &other)
    {

        spenedLimit=other.spenedLimit;
        operationDescription=other.operationDescription;
        prices=other.prices;
        // we do not do any thing for card number to keep it unique
        remaningMoney=other.remaningMoney;
        totalSOps = other.totalSOps;

        return *this;
    }

    // destructor

    ~CardStatement()
    {
        cout<< cardNumber << " Has been destroyed! "<< endl;
    }

    // setter

    void increaseLimit(double limit)
    {

        if(limit> spenedLimit)
        {

            spenedLimit = limit;
        }
        else
        {
            throw logic_error ("Limit should be grater than the existing one.!");
        }
    }

    //getters

    double getLimit() const
    {
        return spenedLimit;
    }

    int getNumber()const
    {

        return cardNumber;
    }

    // add operation method

    void addOperation( string desc, double cost)
    {


        if(cost> remaningMoney)
        {
            operationDescription.push_back(desc);
            prices.push_back(0);
        }
        else
        {
            operationDescription.push_back(desc);
            prices.push_back(cost);
            remaningMoney-=cost;
            totalSOps++;
        }

    }

    // delete unsuccesful method

    void delUnsuccesful()
    {

        for(int i=0; i< prices.size(); i++)
        {
            if(prices[i]==0)
            {
                prices.erase(prices.begin()+i);
                operationDescription.erase(operationDescription.begin()+i);
            }
        }
    }

    static int totalSuccOps()
    {
        return totalSOps;
    }

    // indexing operator

    string &operator [](int position)
    {
        if(position<1 || position>operationDescription.size())
        {
            throw logic_error ("Item not found");
        }

        return operationDescription[position-1];
    }

    // shift operator

    friend ostream &operator <<(ostream &out, const CardStatement &c)
    {
        out<< "card no. "<< c.cardNumber <<"; limit: "<< c.spenedLimit<<" PLN"<<endl;

        int mostExp=-1;
        int total=0;
        double remaining=c.spenedLimit;
        for(int i=0; i<c.operationDescription.size(); i++)
        {
            if(c.prices[i]==0)
            {
                out<< i+1 <<". "<< c.operationDescription[i] <<", " <<c.prices[i]<< " PLN" << " ( Unsuccesful )" <<endl;
            }
            else
            {
                total+=c.prices[i];
                remaining-=c.prices[i];
                if(c.prices[i]>mostExp)
                {
                    mostExp=c.prices[i];
                }
                out<< i+1 <<". "<< c.operationDescription[i] <<", " <<c.prices[i]<< " PLN" <<endl;
            }


        }
        out<< "Total: " << total <<" PLN" <<", " << "remaining: "<<  remaining <<" PLN, " << "most expensive: "<<mostExp <<" PLN" <<endl;

        return out;
    }

    // greater operator

    bool operator >(const CardStatement &c)
    {
        double remaining=spenedLimit;
        for(int i=0;i<prices.size();i++){
            remaining -= prices[i];
        }
        double remainingOfC=c.spenedLimit;
        for(int i=0;i<c.prices.size();i++)
        {
            remainingOfC-=c.prices[i];
        }
        return remaining > remainingOfC;

        //return remaningMoney > c.remaningMoney;
    }
};
int CardStatement::counter=1000;
int CardStatement::totalSOps=0;

#endif // LIB_H
