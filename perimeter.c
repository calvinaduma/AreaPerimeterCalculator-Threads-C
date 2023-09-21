#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// calculates perimeter from 2 inputs
// prints its own and parents pids

int main( int argc, char* argv[] ) {
    if ( argc != 3 ) {
        printf( "ERROR: perimeter.c requires 2 arguments passed in\n" );
        exit( 0 );
    }

    int num1 = atoi( argv[1] );
    int num2 = atoi( argv[2] );

    printf( "Child 2: pid %d, ppid %d, perimeter is %d\n", getpid(), getppid(), 2*(num1+num2) );
    return 0;
}
