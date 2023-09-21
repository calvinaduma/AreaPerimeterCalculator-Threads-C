#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

typedef struct Datas{
	char* word;
	int value1;
    int value2;
} Data;

// reverse string function
char *strrev( char *str ){
	char *p1, *p2;
	if ( !str || !*str )
		return str;
	for ( p1=str, p2=str+strlen( str )-1; p2>p1; ++p1, --p2 ){
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

// thread that returns the ratio of 2 numbers
void *calculateRatioFunc( void* args ){
    Data* threadStruct = ( Data* ) args;
    float* ratio = malloc( sizeof( float ) );
    *ratio  = ( float )threadStruct->value1 / ( float )threadStruct->value2;
    pthread_exit( ( void* )ratio );
}

// thread that returns a reversed string
void *reverseWordFunc( void* args ){
    Data* threadStruct = (Data*) args;
    char* reversedWord = strrev( threadStruct->word );
    pthread_exit( ( void* )reversedWord );
}

int main( int argc, char* argv[] ){

    // check for errors in command line
    if ( argc != 4 ) {
        printf( "ERROR: asg1.c requires 2 arguments to be passed in\n" );
        exit( 0 );
    }

    // assign command line arguments to struct
    Data data = {
	    argv[1],
		atoi(argv[2]),
		atoi(argv[3])
    };

    // start of EXEC code 
    pid_t child_1 = fork(); // first fork 

    // enters child_1 and executes area.c 
    if ( child_1 == 0 ) execl( "./area", "area", argv[2], argv[3], NULL); 

    wait ( NULL ); // waits for child_1 to finish 

    // back in parent 

    pid_t child_2 = fork(); // second fork 

    // enters child_2 and executes perimeter.c 
    if ( child_2 == 0 ) execl( "./perimeter", "perimeter", argv[2], argv[3], NULL); 
     
    wait ( NULL ); // waits for child_2 to finish 
    
    // back in parent 
    
    // start of THREAD code 
    pthread_t thread_1_ID, thread_2_ID;
    char* reversedMessage;
    float* ratio;

    // thread_1 
    pthread_create( &thread_1_ID, NULL, &calculateRatioFunc, &data);
    // thread_2 
    pthread_create( &thread_2_ID, NULL, &reverseWordFunc, &data);

    wait( NULL ); // waits for threads to finish running 

    // join threads 
    pthread_join( thread_1_ID, ( void* )&ratio );
    pthread_join( thread_2_ID, ( void* )&reversedMessage );
    
    // prints results
    printf( "\nThread 1: tid %ld, ratio is %.2f\n", thread_1_ID, *ratio );
    printf( "Thread 2: tid %ld, word is \"%s\"\n", thread_2_ID, reversedMessage );
    printf( "\nParent: pid %d, ratio: %.2f, word is \"%s\"\n", getpid(), *ratio, reversedMessage );
    
    // free memory 
    free( ratio );
    
    return 0;
}
