#ifndef LIB_H_KNOWN
#define LIB_H_KNOWN
#include <vector>
#include <string>
using namespace std;

class Worker
{
private:
    string name;
    float hourly_wage;
    vector<int> time_periods;
    static int ov_count;
    static int tT;

public:
    Worker(string new_name = "NN", float hw = 0.0);
    ~Worker();
    Worker(const Worker &other);
    Worker &operator=(const Worker &other);
    void setName(string new_name);
    string getName() const;
    void setWage(float new_hw);
    float getWage() const;
    void addTime(int hw);
    void modifyTimes();
    int listSize();
    static int totalWorktime();
    float getEarnings();
    static int overTimeWorkers();
    int &operator[](int n);
    friend ostream &operator<<(ostream &os, const Worker &other);
    int totalt() const;
    bool operator>(const Worker &w);
    // ostream & operator << (ostream & os, const Worker & other);
};

#endif
