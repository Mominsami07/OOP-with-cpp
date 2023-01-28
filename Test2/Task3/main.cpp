
#include "Settlement.h"
#include <iostream>
using namespace std;

int main()
{
    Settlement calc("My jobs", 10000);
    cout << "counter of jobs before any actions: " << endl;
    cout << " =========================================" << endl;
    cout << Job::count() << endl; // 0
    cout << " =========================================" << endl;
    cout << "overFlowError because Max gain Exceeded : " << endl;
    cout << " =========================================" << endl;
    try
    {
        calc.add(new TimeJob("salesman", "shop.com", 80, 25));
        calc.add(new TaxedJob("programmer", "Soft", 9000, 18));
        calc.add(new TimeJob("tutor", "University", 100, 6));
        calc.add(new TaxedJob("owner", "MyComp", 3000, 30));
    }
    catch (Settlement::overflowError &e)
    {
        cout << e.what() << endl; // gain for: MyComp is too large
    }
    cout << " =========================================" << endl;
    cout << "Shift operator: " << endl;
    cout << calc;
    cout << " =========================================" << endl;
    //  1. salesman (shop.com ), total gain: 2000
    // 2. programmer (Soft ), total gain: 7380
    // 3. tutor (University ), total gain: 600

    cout << "Check counter after we throw error while adding: " << endl;
    cout << Job::count() << endl; // 3
    cout << " =========================================" << endl;
    cout << "Check Summery Gain: " << endl;
    cout << calc.summaryGain() << endl; // 9980.00
    cout << " =========================================" << endl;
    calc.remove("University");
    cout << "Job counter after removing University " << endl;
    cout << Job::count() << endl;
    cout << " =========================================" << endl;
    cout << "summary Gain after removing University " << endl;
    cout << calc.summaryGain() << endl; // 9380.00
    cout << " =========================================" << endl;
    cout << " summery gain for position 1 in the list and exception for Index error: " << endl;
    try
    {
        cout << calc[1]->getGain() << endl; // 2000.0
        cout << calc[4]->getGain() << endl;
    }
    catch (Settlement::IndexError &e)
    {
        cout << e.what() << endl; // item no.4 not found
    }
    cout << " =========================================" << endl;
    cout << "Check Job count() after clearing the calc class: " << endl;
    calc.clear();

    cout << Job::count() << endl; // 0
    cout << " =========================================" << endl;
    return 0;
}
