# Memory Allocation Lab

A C++ simulation of dynamic memory allocation strategies used in operating systems.

## Features

- First Fit allocation
- Best Fit allocation
- Worst Fit allocation
- Process allocation and deallocation
- Memory layout visualization
- Memory compaction
- Memory utilization calculation
- External fragmentation analysis
- Largest free block detection
- Memory reset

## How It Works

The simulator manages a virtual memory space of 1024 KB.

Processes request memory blocks, and the user can choose different allocation strategies:

### First Fit
Allocates the first available block large enough for the requested memory.

### Best Fit
Allocates the smallest available block that can satisfy the request.

### Worst Fit
Allocates the largest available block.

## Example

```text
============================================================
 MEMORY LAYOUT
============================================================
[   0- 149] P1 | Size: 150 KB
[ 150- 449] P2 | Size: 300 KB
[ 450- 549] P3 | Size: 100 KB
[ 550-1023] FREE | Size: 474 KB
Memory Statistics

The simulator calculates:

Total Memory
Used Memory
Free Memory
Number of Free Blocks
Largest Free Block
Memory Utilization
External Fragmentation

Example:
Total Memory            : 1024 KB
Used Memory             : 400 KB
Free Memory             : 624 KB
Largest Free Block      : 624 KB
Memory Utilization      : 39.06%
External Fragmentation  : 0.00%

Project Structure

MemoryAllocationLab/
│
├── docs/
├── screenshots/
├── tests/
│
├── MemoryBlock.h
├── MemoryBlock.cpp
├── MemoryManager.h
├── MemoryManager.cpp
└── main.cpp

Technologies
C++
Object-Oriented Programming
STL
Vectors
Dynamic Memory Concepts
Operating Systems
Memory Management
Algorithms
Simulation
Learning Objectives

This project demonstrates practical understanding of:

Dynamic memory allocation strategies
Memory fragmentation
Process memory management
Algorithm comparison
Data structure design
Object-oriented programming
Operating system concepts


Build and Run

Open the project using Visual Studio 2022.

Build:

Ctrl + Shift + B

Run without debugging:

Ctrl + F5
Portfolio

This project was developed as a practical demonstration of operating system memory management concepts and algorithmic decision-making.

Disclaimer

This is an educational simulation and does not manage actual system memory.
