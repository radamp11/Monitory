#include "buffer.h"
#include <time.h>


const int MAX_BUFFER = 9;
const int MIN_BUFFER = 3;
const int MAX_SUM_A = 20;

int line = 1;   //just to make outcome clearer

buffer::buffer(){}
buffer::~buffer(){}

int buffer::size() { return buff.size(); }

int buffer::sum() { return sum_of_elems; }

int buffer::front() { return buff.front(); }

void buffer::push( const int elem )
{
    buff.push( elem );
    sum_of_elems += elem;
}

int buffer::pop()
{
    int tmp = buff.front();
    sum_of_elems -= tmp;
    buff.pop();
    return tmp;
}

void buffer::produce_A()
{
    enter();
    if( !(sum() < MAX_SUM_A && size() < MAX_BUFFER) )
    {
        //std::cout << line << ": " << "Prod A zawiesil sie " << std::endl; ++line;
        wait( A_wait );
    }
    push( rand() % 10 + 1 );
    std::cout << line << ": " << "Producer A has added a new element: " << front() << std::endl; ++line;
        //std::cout << line << ": " << "Rozmiar bufora po produkcji: " << size() << std::endl; ++line;
        //std::cout << line << ": " << "Suma suma elementow w buforze po produkcji: " << sum() << std::endl; ++line;

    if( size() == MIN_BUFFER + 1)
    {
            //std::cout << line << ": " << "Prod A wznowil konsumentow " << std::endl; ++line;
        signal( cons_wait );
    }
    leave();
}

void buffer::produce_B()
{
    enter();
    if( !(size() < MAX_BUFFER) ){
            //std::cout << line << ": " << "Prod B zawiesil sie " << std::endl; ++line;
        wait( B_wait );
    }
    push( rand() % 10 + 1 );
    std::cout << line << ": " << "Producer B has added a new element: "<< front() << std::endl; ++line;
        //std::cout << line << ": " << "Rozmiar bufora po produkcji: " << size() << std::endl; ++line;
        //std::cout << line << ": " << "Suma suma elementow w buforze po produkcji: " << sum() << std::endl; ++line;

    if( size() == MIN_BUFFER + 1){
            //std::cout << line << ": " << "Prod B wznowil konsumentow " << std::endl; ++line;
        signal( cons_wait );
    }
    leave();
}

void buffer::consume()
{
    enter();
    if( size() <= MIN_BUFFER ){
        wait( cons_wait );
    }

        std::cout << line << ": " << "Consumer has deleted an element: " << pop() << std::endl; ++line;
            //std::cout << line << ": " << "Rozmiar bufora po konsumpcji: " << size() << std::endl; ++line;
            //std::cout << line << ": " << "Suma suma elementow w buforze po konsumpcji: " << sum() << std::endl; ++line;

        if( sum() < MAX_SUM_A ){
                    //std::cout << line << ": " << "Kons wznowil Prod A " << std::endl; ++line;
                signal( A_wait );
        }
        if( size() < MAX_BUFFER){
                //std::cout << line << ": " << "Kons wznowil Prod B " << std::endl; ++line;
            signal( B_wait );
        }
    leave();
}
