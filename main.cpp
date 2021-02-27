/** Projekt nr 4 - monitory          *
 * Systemy operacyjne - labolatorium *
 * Adam Stec                         *
 * 11.01.2020                        **/


#include "buffer.h"

buffer bufor;

void* producerA_thread( void *th ){

    unsigned int number = *((unsigned int *) th );

    while ( true ) {
        usleep( number );
        bufor.produce_A();
    }
    pthread_exit(NULL);
}

void* producerB_thread( void *th ){
    unsigned int number = *((unsigned int *) th );

    while ( true ) {
        usleep(number);
        bufor.produce_B();
    }
    pthread_exit(NULL);
}

void* consumers_thread( void *th ){
    unsigned int number = *((unsigned int *) th );

    while ( true ) {
        usleep( number );
        bufor.consume();
    }
    pthread_exit(NULL);
}

int main (){
    pthread_t prod_a, prod_b, cons_a, cons_b;

    unsigned int * freq1;
    unsigned int * freq2;
    unsigned int * freq3;
    unsigned int * freq4;

    freq1 = new unsigned int [1000000];
    freq2 = new unsigned int [1000000];
    freq3 = new unsigned int [1000000];
    freq4 = new unsigned int [1000000];

    pthread_create( &prod_a, NULL, producerA_thread, (void*) freq1 );
    pthread_create( &prod_b, NULL, producerB_thread, (void*) freq2 );
    pthread_create( &cons_a, NULL, consumers_thread, (void*) freq3 );
    pthread_create( &cons_b, NULL, consumers_thread, (void*) freq4 );

    pthread_join( prod_a, NULL );
    pthread_join( prod_b, NULL );
    pthread_join( cons_a, NULL );
    pthread_join( cons_b, NULL );

    delete freq1;
    delete freq2;
    delete freq3;
    delete freq4;

    return 0;
}
