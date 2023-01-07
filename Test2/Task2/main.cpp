#include <iostream>
#include <string>
#include "Schedule.h"
#include "Work.h"
using namespace std;
int main()
{
    Schedule repairs("Expected repairs of my room", 2000); // budget=2000€
    std::cout << Work::count() << "\n";                    // 0

    try
    {
        repairs.insert(1, new FieldWork("floor", "John", 4.5, 6, 30));     // 4.5x6, 30€
        repairs.insert(2, new FieldWork("walls", "Luke", 21, 2.5, 15));    // 21x2.5, 15€
        repairs.insert(1, new PieceWork("electric points", "Ben", 7, 20)); // 7pcs, 20€
        repairs.insert(4, new TimeWork("cleaning", "Mary", 18, 10));       // 18h, 10€
        repairs.insert(4, new PieceWork("lighting", "Tom", 4, 30));        // 4pcs, 30€
    }
    catch (Schedule::DeficitError &e)
    {
        std::cout << e.what() << std::endl; // lighting too expensive - only 102.50 free money
    }

    std::cout << repairs;
    // Expected repairs of my room, total budget: 2000.00, remaining money: 102.50:
    // 1. electric points (Ben), cost: 140.00
    // 2. floor (John), cost: 810.00
    // 3. walls (Luke), cost: 787.50
    // 4. cleaning (Mary), cost: 160.00
    std::cout << Work::count() << "\n";         // 4
    std::cout << repairs.summaryCost() << "\n"; // 1897.50
    repairs.removeFirst();
    std::cout << Work::count() << "\n";         // 3
    std::cout << repairs.summaryCost() << "\n"; // 1757.50
    try
    {
        std::cout << repairs[1].getCost() << "\n"; // 810.00
        std::cout << repairs[5].getCost() << "\n"; // IndexError exception
    }
    catch (Schedule::IndexError &e)
    {
        std::cout << e.what() << "\n";
    }
    repairs.clear();
    std::cout << Work::count(); // 0

    return 0;
}
