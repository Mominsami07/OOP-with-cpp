
#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include<string>
#include <iostream>
#include<stdexcept>
#include <vector>
#include<ostream>
#include"Job.h"
class Settlement
{
protected:
    string description;
    double maxGain;
    double remainingGain=maxGain;
    vector<Job*> jobs;

public:
    class overflowError : public overflow_error
    {
    public:
        overflowError(string msg="something wrong"): overflow_error(msg) {}
    };
    class NameError : public logic_error
    {
    public:
        NameError(string msg="something wrong"): logic_error(msg) {}
    };
    class IndexError : public logic_error
    {
    public:
        IndexError(string msg="something wrong"): logic_error(msg) {}
    };
    Settlement(string desc,double mxG): description(desc),maxGain(mxG)
    {

    }
    ~Settlement()
    {
        clear();
    }

    void clear()
    {
        for(auto c:jobs)
        {
            delete c;
        }
        jobs.clear();
    }
    void add( Job *j)
    {

        if(j->getGain() > maxGain || j->getGain() > remainingGain)
        {
            string info = "gain for: " + j->getCompanyName() + " is too large";
            delete j;
            throw overflowError(info);
        }

        jobs.push_back(j);
        remainingGain-= j->getGain();
    }

    double summaryGain()
    {
        double totalGain=0;
        for(auto c: jobs)
        {
            totalGain+= c->getGain();

        }

        return totalGain;
    }

    void remove(string jName)
    {
        bool found =false;

        for(int i=0; i<jobs.size(); i++)
        {
            if(jobs[i]->getCompanyName() == jName)
            {
                found=true;
                delete jobs[i];
                jobs.erase(jobs.begin()+i);
            }

        }
        if(!found)
        {
            string info = jName + "does not exist! ";
            throw NameError(info);
        }
    }
    friend ostream &operator <<(ostream &out, const Settlement &s)
    {
        double totalGain=0;
        for(auto c: s.jobs)
        {
            totalGain+= c->getGain();
        }
        out<< s.description<<", maximal gain: "<< s.maxGain << ", TotalGain: "<< totalGain<< endl;
        int i=0;
        for(auto c :s.jobs){
            out<<i+1 <<". "<< c->getPosition() << " (" << c->getCompanyName() << " )," <<" total gain: "<< c->getGain() <<endl;
            i++;
        }

        return out;
    }

    Job* operator [] (int pos)
    {
        if(pos<0 || pos> jobs.size())
        {
            string info = "item no. "+ to_string(pos) + "not found";
            throw IndexError(info);
        }

        return jobs[pos-1];
    }

};

#endif // SETTLEMENT_H
