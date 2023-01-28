
#ifndef JOB_H
#define JOB_H
#include <iostream>
#include <string>
using namespace std;

class Job
{
protected:
    string position;
    string companyName;
    static int numOfJobs;

public:
    Job(string pos, string coName):position(pos),companyName(coName)
    {
        numOfJobs++;
    }
    virtual ~Job()
    {
        numOfJobs--;
    }

    virtual double getGain() =0;

    string getPosition()
    {
        return position;
    }
    string getCompanyName()
    {
        return companyName;
    }
    static int count()
    {
        return numOfJobs;
    }
};
int Job::numOfJobs=0;

class TaxedJob :public Job
{
protected:
    double income;
    double taxPerc;

public:
    TaxedJob(string pos,string cName,double inc,double tax):Job(pos,cName),income(inc),taxPerc(tax)
    {
    }
    ~TaxedJob() {}
    double getGain()
    {
        double reducedAmount = income * (taxPerc/100);

        return income - reducedAmount;
    }
};

class TimeJob :public Job
{
protected:
    double income;
    double numOfhours;

public:
    TimeJob(string pos,string cName,double inc,double hours):Job(pos,cName),income(inc),numOfhours(hours)
    {
    }
    ~TimeJob() {}
    double getGain()
    {

        return income*numOfhours;
    }

};
#endif // JOB_H
