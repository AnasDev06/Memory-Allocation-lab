#pragma once

#include "MemoryBlock.h"

#include <string>
#include <vector>

enum class AllocationStrategy
{
    FirstFit,
    BestFit,
    WorstFit
};

class MemoryManager
{
private:
    std::vector<MemoryBlock> blocks;
    int totalMemory;

    int findFreeBlock(
        int requiredSize,
        AllocationStrategy strategy
    ) const;

    void splitBlock(
        int blockIndex,
        int requiredSize,
        const std::string& processId
    );

public:
    explicit MemoryManager(int totalMemory);

    bool allocate(
        const std::string& processId,
        int size,
        AllocationStrategy strategy
    );

    bool deallocate(
        const std::string& processId
    );

    void compact();

    void reset();

    void printMemoryLayout() const;
    void printStatistics() const;

    int getUsedMemory() const;
    int getFreeMemory() const;
    int getLargestFreeBlock() const;
    double getUtilization() const;

    const std::vector<MemoryBlock>& getBlocks() const;
};