#include "MemoryManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>

MemoryManager::MemoryManager(int totalMemory)
    : totalMemory(totalMemory)
{
    blocks.emplace_back(
        0,
        totalMemory,
        true
    );
}

int MemoryManager::findFreeBlock(
    int requiredSize,
    AllocationStrategy strategy
) const
{
    int selected = -1;

    for (int i = 0; i < static_cast<int>(blocks.size()); ++i)
    {
        if (!blocks[i].isFree())
        {
            continue;
        }

        if (blocks[i].getSize() < requiredSize)
        {
            continue;
        }

        if (strategy == AllocationStrategy::FirstFit)
        {
            return i;
        }

        if (selected == -1)
        {
            selected = i;
            continue;
        }

        if (strategy == AllocationStrategy::BestFit)
        {
            if (blocks[i].getSize() <
                blocks[selected].getSize())
            {
                selected = i;
            }
        }
        else if (strategy == AllocationStrategy::WorstFit)
        {
            if (blocks[i].getSize() >
                blocks[selected].getSize())
            {
                selected = i;
            }
        }
    }

    return selected;
}

void MemoryManager::splitBlock(
    int blockIndex,
    int requiredSize,
    const std::string& processId
)
{
    MemoryBlock original = blocks[blockIndex];

    blocks[blockIndex] = MemoryBlock(
        original.getStartAddress(),
        requiredSize,
        false,
        processId
    );

    const int remaining =
        original.getSize() - requiredSize;

    if (remaining > 0)
    {
        blocks.insert(
            blocks.begin() + blockIndex + 1,
            MemoryBlock(
                original.getStartAddress() + requiredSize,
                remaining,
                true
            )
        );
    }
}

bool MemoryManager::allocate(
    const std::string& processId,
    int size,
    AllocationStrategy strategy
)
{
    if (size <= 0)
    {
        return false;
    }

    for (const MemoryBlock& block : blocks)
    {
        if (!block.isFree() &&
            block.getProcessId() == processId)
        {
            return false;
        }
    }

    const int blockIndex =
        findFreeBlock(size, strategy);

    if (blockIndex == -1)
    {
        return false;
    }

    splitBlock(
        blockIndex,
        size,
        processId
    );

    return true;
}

bool MemoryManager::deallocate(
    const std::string& processId
)
{
    for (int i = 0; i < static_cast<int>(blocks.size()); ++i)
    {
        if (!blocks[i].isFree() &&
            blocks[i].getProcessId() == processId)
        {
            blocks[i].release();

            // Merge with previous block.
            if (i > 0 && blocks[i - 1].isFree())
            {
                const int newSize =
                    blocks[i - 1].getSize() +
                    blocks[i].getSize();

                const int start =
                    blocks[i - 1].getStartAddress();

                blocks[i - 1] =
                    MemoryBlock(
                        start,
                        newSize,
                        true
                    );

                blocks.erase(
                    blocks.begin() + i
                );

                --i;
            }

            // Merge with next block.
            if (i + 1 < static_cast<int>(blocks.size()) &&
                blocks[i + 1].isFree())
            {
                const int newSize =
                    blocks[i].getSize() +
                    blocks[i + 1].getSize();

                blocks[i] =
                    MemoryBlock(
                        blocks[i].getStartAddress(),
                        newSize,
                        true
                    );

                blocks.erase(
                    blocks.begin() + i + 1
                );
            }

            return true;
        }
    }

    return false;
}

void MemoryManager::compact()
{
    std::vector<MemoryBlock> compacted;

    int currentAddress = 0;

    for (const MemoryBlock& block : blocks)
    {
        if (!block.isFree())
        {
            compacted.emplace_back(
                currentAddress,
                block.getSize(),
                false,
                block.getProcessId()
            );

            currentAddress += block.getSize();
        }
    }

    if (currentAddress < totalMemory)
    {
        compacted.emplace_back(
            currentAddress,
            totalMemory - currentAddress,
            true
        );
    }

    blocks = compacted;
}

void MemoryManager::reset()
{
    blocks.clear();

    blocks.emplace_back(
        0,
        totalMemory,
        true
    );
}

int MemoryManager::getUsedMemory() const
{
    int used = 0;

    for (const MemoryBlock& block : blocks)
    {
        if (!block.isFree())
        {
            used += block.getSize();
        }
    }

    return used;
}

int MemoryManager::getFreeMemory() const
{
    return totalMemory - getUsedMemory();
}

int MemoryManager::getLargestFreeBlock() const
{
    int largest = 0;

    for (const MemoryBlock& block : blocks)
    {
        if (block.isFree())
        {
            largest =
                std::max(
                    largest,
                    block.getSize()
                );
        }
    }

    return largest;
}

double MemoryManager::getUtilization() const
{
    if (totalMemory == 0)
    {
        return 0.0;
    }

    return
        static_cast<double>(getUsedMemory()) /
        totalMemory * 100.0;
}

void MemoryManager::printMemoryLayout() const
{
    std::cout << "\n============================================================\n";
    std::cout << " MEMORY LAYOUT\n";
    std::cout << "============================================================\n";

    for (const MemoryBlock& block : blocks)
    {
        std::cout
            << "["
            << std::setw(4)
            << block.getStartAddress()
            << "-"
            << std::setw(4)
            << block.getEndAddress()
            << "] ";

        if (block.isFree())
        {
            std::cout
                << "FREE";
        }
        else
        {
            std::cout
                << block.getProcessId();
        }

        std::cout
            << " | Size: "
            << block.getSize()
            << " KB\n";
    }
}

void MemoryManager::printStatistics() const
{
    int freeBlocks = 0;

    for (const MemoryBlock& block : blocks)
    {
        if (block.isFree())
        {
            ++freeBlocks;
        }
    }

    const int freeMemory =
        getFreeMemory();

    const int largestFree =
        getLargestFreeBlock();

    double externalFragmentation = 0.0;

    if (freeMemory > 0)
    {
        externalFragmentation =
            (1.0 -
                static_cast<double>(largestFree) /
                freeMemory) * 100.0;
    }

    std::cout << "\n============================================================\n";
    std::cout << " MEMORY STATISTICS\n";
    std::cout << "============================================================\n";

    std::cout << "Total Memory            : "
        << totalMemory
        << " KB\n";

    std::cout << "Used Memory             : "
        << getUsedMemory()
        << " KB\n";

    std::cout << "Free Memory             : "
        << freeMemory
        << " KB\n";

    std::cout << "Free Blocks             : "
        << freeBlocks
        << "\n";

    std::cout << "Largest Free Block     : "
        << largestFree
        << " KB\n";

    std::cout << std::fixed
        << std::setprecision(2);

    std::cout << "Memory Utilization      : "
        << getUtilization()
        << "%\n";

    std::cout << "External Fragmentation  : "
        << externalFragmentation
        << "%\n";
}

const std::vector<MemoryBlock>& MemoryManager::getBlocks() const
{
    return blocks;
}