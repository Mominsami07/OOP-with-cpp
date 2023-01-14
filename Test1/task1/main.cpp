
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Product
{
private:
    string name;
    int id;
    static int counter;
    vector<string> destinations;
    vector<int> amount;
    static int total;

public:
    // default constructor
    Product(string pName = "")
    {
        name = pName;
        counter++;
        id = counter;
    }

    // destructor
    ~Product()
    {
        cout << name << " has been destroyed" << endl;
    }
    // copy constructor

    Product(const Product &other)
    {
        name = other.name;
        if (!other.destinations.empty())
        {
            destinations = other.destinations;
        }
        if (!other.amount.empty())
        {
            amount = other.amount;
        }
        int sum = 0;
        for (int i = 0; i < other.amount.size(); i++)
        {
            sum = sum + amount[i];
        }
        total = total + sum;
        counter++;
        id = counter;
    }

    // assignment operator

    Product &operator=(const Product &x)
    {
        // we should subtract the ammount in this from total
        int sum = 0;
        for (int i = 0; i < amount.size(); i++)
        {
            sum = sum + amount[i];
        }
        total = total - sum;

        name = x.name;
        destinations = x.destinations;
        amount = x.amount;
        //         counter++;
        //         id = counter;

        // we should not do anything for ids

        // we should add the amount from x
        sum = 0;
        for (int i = 0; i < x.amount.size(); i++)
        {
            sum = sum + x.amount[i];
        }
        total = total + sum;

        return *this;
    }

    // shift operator

    friend ostream &operator<<(ostream &os, const Product &x)
    {
        int total = 0;
        int numOfDest = 0;
        int maxAmount = -1;
        string maxDest = "";
        os << "Delivery list for: " << x.name << " (ID " << x.id << ") :" << endl;
        for (int i = 0; i < x.destinations.size(); i++)
        {
            total = total + x.amount[i];
            numOfDest++;
            os << i + 1 << ". " << x.destinations[i] << " - " << x.amount[i] << endl;
            if (x.amount[i] > maxAmount)
            {
                maxAmount = x.amount[i];
                maxDest = x.destinations[i];
            }
        }
        double average = (double)total / numOfDest;
        os << "Total: " << total << ", average: " << average << ", max: " << maxAmount << " (to " << maxDest << " )" << endl;
        return os;
    }

    // indexing operator
    string &operator[](int position)
    {
        if (position > destinations.size() || position < 1)
        {
            throw logic_error("position does not exist!");
        }
        return destinations[position - 1];
    }

    // grater than operator

    bool operator>(const Product &x)
    {
        int sumOfx = 0;
        for (int i = 0; i < x.amount.size(); i++)
        {
            sumOfx += x.amount[i];
        }
        int sum = 0;
        for (int i = 0; i < amount.size(); i++)
        {
            sum += amount[i];
        }

        return sum > sumOfx;
    }
    // greatest order destination

    string greatestOrderDest()
    {
        int maxAmount = -1;
        string maxDest = "";
        for (int i = 0; i < amount.size(); i++)
        {
            if (amount[i] > maxAmount)
            {
                maxAmount = amount[i];
                maxDest = destinations[i];
            }
        }
        return maxDest;
    }

    // add order method

    void addOrder(string dest, int pAmount)
    {
        bool found = false;
        total = total + pAmount;
        for (int i = 0; i < destinations.size(); i++)
        {
            if (destinations[i] == dest)
            {
                amount[i] = amount[i] + pAmount;
                found = true;
                break;
            }
        }
        if (!found)
        {
            destinations.push_back(dest);
            amount.push_back(pAmount);
        }
    }

    // Delete destinations
    void deleteDestination(string dest)
    {
        bool found = false;
        for (int i = 0; i < destinations.size(); i++)
        {
            if (destinations[i] == dest)
            {
                total = total - amount[i];
                destinations.erase(destinations.begin() + i);
                amount.erase(amount.begin() + i);
                found = true;
            }
        }
        if (!found)
        {
            throw logic_error("destination does not exist!");
        }
    }

    // numberOfDest method
    int numberOfDest()
    {
        int num = 0;
        for (int i = 0; i < destinations.size(); i++)
        {
            num++;
        }
        return num;
    }

    // totalAmount method

    static int totalAmount()
    {
        return total;
    }
    // set name

    void setName(string n)
    {
        name = n;
    }

    // get name
    string getName()
    {
        return name;
    }

    // get id
    int getID()
    {
        return id;
    }
};

int Product::counter = 0;
int Product::total = 0;
int main()
{
    cout << Product::totalAmount() << endl; // should be 0
    Product p1("HP DeskJet 3110 printer");
    cout << p1.getName() << ", ID: " << p1.getID() << endl; // HP DeskJet 3110 printer, ID: 1
    p1.addOrder("Warsaw", 20);
    p1.addOrder("Gdansk", 30);
    p1.addOrder("Warsaw", 20);
    // p1.addOrder("Lodz",50);
    cout << p1.numberOfDest() << endl;      // should be 2
    cout << p1.greatestOrderDest() << endl; // should print warsaw
    p1[2] = "Lodz";                         // Changes the second destination city
    cout << p1;
    Product p2(p1);
    p2.setName("Canon TS205 printer");
    p2.addOrder("Gdansk", 25);
    p2.addOrder("Lodz", 30);
    cout << Product::totalAmount() << endl; // should be 195

    if (p2 > p1)
    {
        cout << "amount of " << p2.getName() << " greater than of " << p1.getName() << endl;
    }
    p2.deleteDestination("Warsaw");
    cout << p2;
    cout << Product::totalAmount() << endl; // should be 155
    return 0;
}
