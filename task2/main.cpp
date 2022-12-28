// Define the class PizzeriaOrder representing a list of dishes a customer orders in a pizzeria
// link https://imul.math.uni.lodz.pl/~polrola/strony/oop21/test1_21.pdf
#include <iostream>
#include <vector>
using namespace std;

class PizzaOrder
{
private:
    string customer_name;
    vector<string> dishes;
    vector<double> prices;
    static int dishes_count;

public:
    // default constructor
    PizzaOrder(string cname = "")
    {
        customer_name = cname;
    }

    // destructor
    ~PizzaOrder()
    {
        cout << "order has been destroyed" << endl;

        dishes_count = dishes_count - dishes.size();
    }

    // copy constructor
    PizzaOrder(const PizzaOrder &other)
    {
        customer_name = other.customer_name;
        if (!other.dishes.empty())
        {
            dishes = other.dishes;
        }
        if (!other.prices.empty())
        {
            prices = other.prices;
        }
        dishes_count = dishes_count + other.dishes.size();
    }

    // assignment operator

    PizzaOrder &operator=(const PizzaOrder x)
    {
        customer_name = x.customer_name;
        dishes = dishes;
        prices = prices;

        return *this;
    }
    // smaller than operator

    bool operator<(const PizzaOrder &x)
    {
        return dishes.size() < x.dishes.size();
    }

    // indexing operator
    double &operator[](string dName)
    {
        int index = -1;
        for (int i = 0; i < dishes.size(); i++)
        {
            if (dishes[i] == dName)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            throw logic_error("Dish does not exist!");
        }
        return prices[index];
    }

    // shift operator

    friend ostream &operator<<(ostream &os, const PizzaOrder &x)
    {
        double tc = 0;
        os << "customer: " << x.customer_name << endl;

        for (int i = 0; i < x.dishes.size(); i++)
        {
            os << i + 1 << ". " << x.dishes[i] << ", " << x.prices[i] << endl;
            tc = tc + x.prices[i];
        }
        os << "Total Cost: " << tc << endl;
        return os;
    }

    // getDishesCount method note: that this function should be static so you can call it like that : PizzaOrder::getDishesCount()
    static int getDishesCount()
    {
        return dishes_count;
    }

    // set customer name

    void setCustomer(string cname)
    {
        customer_name = cname;
        // note you can do it like that, and If you want you can do valiidation before setting new name
    }
    // get customer name
    string getCustomer()
    {
        return customer_name;
    }

    // totalCost method

    double totalCost()
    {
        double tc = 0;
        for (int i = 0; i < prices.size(); i++)
        {
            tc += prices[i];
        }

        return tc;
    }

    // Add dish method

    void addDish(string dName, double dPrice)
    {
        dishes.push_back(dName);
        prices.push_back(dPrice);
        dishes_count++;
    }

    // removeDish method

    void removeDish(string dName)
    {
        bool found = false;
        for (int i = 0; i < dishes.size(); i++)
        {
            if (dishes[i] == dName)
            {
                dishes.erase(dishes.begin() + i);
                prices.erase(prices.begin() + i);
                dishes_count--;
                found = true;
                break;
            }
        }

        if (!found)
        {
            throw logic_error("Dish does not exist!");
        }
    }
};

int PizzaOrder::dishes_count = 0;

int main()
{
    cout << PizzaOrder::getDishesCount() << endl; // should be 0
    PizzaOrder o1("John Smith");
    cout << o1.getCustomer() << endl; // should be John Smith
    o1.addDish("garlic bread", 10);
    o1.addDish("Margherita pizza", 25);
    cout << o1.totalCost() << endl; // should be 35

    o1["Margherita pizza"] = 23; // changes the price of the dish
    cout << o1;                  // should print for example:
    // customer: John Smith
    // 1. garlic bread, 10
    // 2. Margherita pizza, 23
    // Total cost: 33

    PizzaOrder oo("Andrew Taylor");
    oo.addDish("fried zucchini", 15);
    oo.addDish("tuna pizza", 35);
    oo.addDish("beer", 5);
    if (o1 < oo)
        cout << "order " << o1.getCustomer() << " ordered smaller number of dishes than " << oo.getCustomer() << endl; // the message should be printed
    oo.removeDish("fried zucchini");
    cout << oo; // should print for example:
    // customer: Andrew Taylor
    // 1. tuna pizza, 35
    // 2. beer, 5
    // Total cost: 40
    cout << PizzaOrder::getDishesCount() << endl; // should be 4

    return 0;
}
