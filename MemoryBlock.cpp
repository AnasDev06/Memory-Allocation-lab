#include "MemoryBlock.h"

MemoryBlock::MemoryBlock(
    int startAddress,
    int size,
    bool free,
    const std::string& processId
)
    : startAddress(startAddress),
    size(size),
    free(free),
    processId(processId)
{}

int MemoryBlock::getStartAddress() const
{
    return startAddress;
}

int MemoryBlock::getSize() const
{
    return size;
}

int MemoryBlock::getEndAddress() const
{
    return startAddress + size - 1;
}

bool MemoryBlock::isFree() const
{
    return free;
}

std::string MemoryBlock::getProcessId() const
{
    return processId;
}

void MemoryBlock::allocate(
    const std::string& processId
)
{
    free = false;
    this->processId = processId;
}

void MemoryBlock::release()
{
    free = true;
    processId.clear();
}