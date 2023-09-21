#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// calculates the area after of 2 inputs
// prints its own and parent pids
int main( int argc, char* argv[] ) {
    if ( argc != 3 ) {
        printf( "ERROR: area.c requires 2 arguments passed in\n" );
        exit( 0 );
    }
    int num1 = atoi( argv[1] );
    int num2 = atoi( argv[2] );

    printf( "Child 1: pid %d, ppid %d, area is %d\n", getpid(), getppid(), num1*num2 );
    return 0;
}
