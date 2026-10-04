# Architecture

* Overview

Memory Allocation Lab is a C++ simulation that models dynamic memory allocation inside a virtual 1024 KB memory space.

The project separates memory representation from memory management logic and the console interface.

* Components

* MemoryBlock

Represents a single contiguous region of virtual memory.

Responsibilities:

- Store start address
- Store block size
- Track whether the block is free
- Store the process ID
- Allocate a process
- Release a process

* MemoryManager

Controls the complete virtual memory space.

Responsibilities:

- Allocate memory
- Deallocate processes
- Apply allocation strategies
- Split free blocks
- Merge adjacent free blocks
- Compact memory
- Calculate memory statistics

* Main

Provides the interactive console interface.

Responsibilities:

- Display the menu
- Read user input
- Select allocation strategies
- Display memory information
- Coordinate operations

* Allocation Strategies

* First Fit

Searches from the beginning and selects the first suitable free block.

* Best Fit

Searches all available blocks and selects the smallest suitable block.

* Worst Fit

Searches all available blocks and selects the largest suitable block.

** Memory Compaction

Compaction moves allocated blocks toward the beginning of memory and combines the remaining free space into one large block.

This reduces external fragmentation.

* Data Structure

The simulator uses:

```text
std::vector<MemoryBlock>

The vector represents memory as an ordered collection of contiguous blocks.

Design Approach

The project follows basic Object-Oriented Design principles:

Encapsulation
Separation of responsibilities
Abstraction
Modular components