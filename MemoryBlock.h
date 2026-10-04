#pragma once

#include <string>

class MemoryBlock
{
private:
    int startAddress;
    int size;
    bool free;
    std::string processId;

public:
    MemoryBlock(
        int startAddress,
        int size,
        bool free = true,
        const std::string& processId = ""
    );

    int getStartAddress() const;
    int getSize() const;
    int getEndAddress() const;

    bool isFree() const;

    std::string getProcessId() const;

    void allocate(const std::string& processId);
    void release();
};