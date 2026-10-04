#include "MemoryManager.h"

#include <iostream>
#include <limits>
#include <string>

AllocationStrategy chooseStrategy()
{
    std::cout << "\nAllocation Strategy:\n";
    std::cout << "1. First Fit\n";
    std::cout << "2. Best Fit\n";
    std::cout << "3. Worst Fit\n";
    std::cout << "Choose: ";

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        return AllocationStrategy::FirstFit;

    case 2:
        return AllocationStrategy::BestFit;

    case 3:
        return AllocationStrategy::WorstFit;

    default:
        return AllocationStrategy::FirstFit;
    }
}

void printMenu()
{
    std::cout << "\n============================================================\n";
    std::cout << " MEMORY ALLOCATION LAB\n";
    std::cout << "============================================================\n";

    std::cout << "1. Allocate Memory\n";
    std::cout << "2. Deallocate Process\n";
    std::cout << "3. Show Memory Layout\n";
    std::cout << "4. Show Statistics\n";
    std::cout << "5. Compact Memory\n";
    std::cout << "6. Reset Memory\n";
    std::cout << "0. Exit\n";
}

int main()
{
    constexpr int TOTAL_MEMORY = 1024;

    MemoryManager manager(
        TOTAL_MEMORY
    );

    while (true)
    {
        printMenu();

        std::cout << "\nChoose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 0)
        {
            std::cout
                << "\nMemory Allocation Lab closed.\n";

            break;
        }

        switch (choice)
        {
        case 1:
        {
            std::string processId;
            int size;

            std::cout
                << "\nProcess ID: ";

            std::cin >> processId;

            std::cout
                << "Memory size (KB): ";

            std::cin >> size;

            AllocationStrategy strategy =
                chooseStrategy();

            if (manager.allocate(
                processId,
                size,
                strategy))
            {
                std::cout
                    << "\nAllocation successful.\n";
            }
            else
            {
                std::cout
                    << "\nAllocation failed.\n";
            }

            break;
        }

        case 2:
        {
            std::string processId;

            std::cout
                << "\nProcess ID: ";

            std::cin >> processId;

            if (manager.deallocate(
                processId))
            {
                std::cout
                    << "\nProcess deallocated.\n";
            }
            else
            {
                std::cout
                    << "\nProcess not found.\n";
            }

            break;
        }

        case 3:
            manager.printMemoryLayout();
            break;

        case 4:
            manager.printStatistics();
            break;

        case 5:
            manager.compact();

            std::cout
                << "\nMemory compacted successfully.\n";

            break;

        case 6:
            manager.reset();

            std::cout
                << "\nMemory reset successfully.\n";

            break;

        default:
            std::cout
                << "\nInvalid option.\n";
        }
    }

    return 0;
}