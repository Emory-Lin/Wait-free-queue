# Wait-free-queue

We compare the speed of three many-to-one communication channels which are obstruction-free queue, lock-free Treiber stack, and our new wait-free queue. 

## Description

We present the  design of a concurrent FIFO queue based on fetch-and-store and compare-and-swap which can be used in the many-to-one communications. It  

- guarantees FIFO ordering of lock acquisitions;
- guarantees that every call finishes its execution in a finite number of steps
- runs faster than obstruction-free stack and lock-free **queue

An empirical study of our queue under high contention with many hardware threads shows that it outperforms prior many-to-one data structure designs that lack wait-free guarantee.

## Getting Started


### Compilering 

In the project directory, you can run:

##### `g++ -o test test.cpp -std=c++11 -Xclang -fopenmp -lomp`

### Executing program

##### `./test`

### Executing the drawing program

##### `python3 ./draw.py`
