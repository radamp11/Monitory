#ifndef BUFFER_H
#define BUFFER_H
#include "monitor.h"
#include <queue>
#include <iostream>

class buffer : Monitor
{
private:
    std::queue<int> buff;
    unsigned int sum_of_elems;
    Condition A_wait, B_wait, cons_wait;
public:
    buffer();
    int size();
    int sum();
    void push( const int elem );
    int pop();
    int front();

    void consume();
    void produce_A();
    void produce_B();

    ~buffer();
};

#endif // BUFFER_H
