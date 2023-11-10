Brief information about algorithms and data structures.

## Data structures

| Name structure     | Indexation  | Search         | Inserting       | Deleting    | Memory |
|:------------------:|:-----------:|:--------------:|:---------------:|:-----------:|:------:|
| Binary Heap        | -           | -              | O(log(n))       | O(log(n))   | O(n)   |
| Binary Tree        | O(log(n))   | O(log(n))      | O(log(n))       | O(log(n))   | O(n)   |
| LinkedList         | O(n)        | O(n)           | O(1)            | O(1)        | O(n)   |
| Hash Table         | O(1)        | O(1)           | O(1)            | O(1)        | O(n)   |
| Queue              | -           | -              | O(1)            | O(1)        | O(n)   |
| Stack              | -           | -              | O(1)            | O(1)        | O(n)   |

## STL containers

| Name STL container | Indexation  | Search         | Inserting       | Deleting    | Memory | Iterator invalidation | Iterator category |
|:------------------:|:-----------:|:--------------:|:---------------:|:-----------:|:------:|:---------------------:|:------------------|
| array              | O(1)        | -              | -               | -           | O(n)   |           +           |         RA        |
| vector             | O(1)        | -              | O(1) back       | O(n)        | O(n)   |           +           |         RA        |
| list               | O(n)        | O(n)           | O(1)            | O(1)        | O(n)   |           -           |         BD        |
| forward_list       | O(n)        | O(n)           | O(1) front      | O(1) front  | O(n)   |           -           |         F         |
| deque              | O(1)        | O(1)           | O(1) back,front | O(1)        | O(n)   |           +           |         RA        |
| unordered_set      | O(1)        | O(1)           | O(1)            | O(1)        | O(n)   |           +           |         F         |
| unordered_map      | O(1)        | O(1)           | O(1)            | O(1)        | O(n)   |           +           |         F         |
| unordered_multiset | O(1)        | O(1)           | O(1)            | O(1)        | O(n)   |           -           |         F         |
| unordered_multimap | O(1)        | O(1)           | O(1)            | O(1)        | O(n)   |           -           |         F         |
| set                | O(log(n))   | O(log(n))      | O(log(n))       | O(log(n))   | O(n)   |           -           |         BD        |
| map                | O(log(n))   | O(log(n))      | O(log(n))       | O(log(n))   | O(n)   |           -           |         BD        |
| multiset           | O(log(n))   | O(log(n))      | O(log(n))       | O(log(n))   | O(n)   |           -           |         BD        |
| multimap           | O(log(n))   | O(log(n))      | O(log(n))       | O(log(n))   | O(n)   |           -           |         BD        |

## STL adapters

| Name STL adapter   | Indexation  | Search         | Inserting       | Deleting    | Memory |
|:------------------:|:-----------:|:--------------:|:---------------:|:-----------:|:------:|
| queue              | -           | -              | O(1)            | O(1)        | O(n)   |
| stack              | -           | -              | O(1)            | O(1)        | O(n)   |
| priority_queue     | -           | -              | O(log(n))       | O(log(n))   | O(n)   |

## Search

| Name algorithm    | Data Structure | Average result | Worse result |
|:-----------------:|:--------------:|:--------------:|:------------:|
| Binary search     | Sorted array   | O(log(n))      | O(log(n))    |
| Linear search     | Array          | O(n)           | O(n)         |

## SmartPointers

| Name pointer                             |
|:----------------------------------------:|
| Auto smart pointer                       |
| Unique smart pointer                     |
| Shared smart pointer                     |

## Sorting

| Name algorithm    |Data Structure | Best result  | Average result | Worse result |
|:-----------------:|:-------------:|:------------:|:--------------:|:------------:|
| Bubble sorting    |  Array        | O(n)         | O(n^2)         | O(n^2)       |
| Bucket sorting    |  Array        | O(n)         | O(n)           | O(n^2)       |
| Counting sorting  |  Array        | O(n)         | O(n)           | O(n)         |
| Insertion sorting |  Array        | O(n^2)       | O(n^2)         | O(n^2)       |
| Merge sorting     |  Array        | O(n*log(n))  | O(n*log(n))    | O(n*log(n))  |
| Quick sorting     |  Array        | O(n*log(n))  | O(n*log(n))    | O(n^2)       |
| Selection sorting |  Array        | O(n)         | O(n^2)         | O(n^2)       |
| Shell sorting     |  Array        | O(n^2)       | O(n^2)         | O(n^2)       |
| Stupid sorting    |  Array        | O(n)         | O(n^3)         | O(n^3)       |
