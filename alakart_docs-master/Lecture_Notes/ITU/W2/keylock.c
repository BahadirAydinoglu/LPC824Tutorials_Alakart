
// Ahmet Onat 2022

//Compile with your favorite C compiler.
// I suggest compiling with:
// gcc -o keylock keylock.c

#include <stdio.h>


// These are the states.
// The actual value is not important.
// We compare the symbols. See the switch statement.
#define START 0
#define C1 1
#define C2 2
#define C3 3

// The correct key sequence:
#define CORRECT1 3
#define CORRECT2 1
#define CORRECT3 2
#define CORRECT4 4

#define FALSE 0
#define TRUE 1



void main(void){


  int state = START; // Initialize to the start state
  int key;
  int door_open=FALSE;

  printf ("\nThis program demonstrates the state diagram approach to writing programs.\n");
  printf ("We are trying to open a door by punching in the correct key sequence.\n");
  printf ("Hint: the correct sequence is: %d, %d, %d, %d\n", CORRECT1, CORRECT2, CORRECT3, CORRECT4 );
  printf ("Now enter a sequence of numbers from 1 to 4:\n\n");
  
  
  while (door_open==FALSE){

    // Print the state, input and output  values.
    // This is for observing what happens 
    //   within the state machine.
    if (state==START){
      printf("state= START\n");
    }else if (state==C1){
      printf("state= C1\n");
    }else if (state==C2){
      printf("state= C2\n");
    }else if (state==C3){
      printf("state= C3\n");
    }
    
    printf("Keypad:");  // Get the next key
    scanf ("%d", &key);
    
    // This is the actual state machine:
    switch (state){    
      
    case START:  // In the start state:
      if (key==CORRECT1){
	state=C1;
	door_open=FALSE;
      }else{
	state=START;
	door_open=FALSE;
      }	
      
      break;
      
    case C1:    // In the C1 state
      if (key==CORRECT2){ // Depending on inputs,
	state=C2;        // the next state will be this
	door_open=FALSE;
      }else{
	state=START;    // or this.
	door_open=FALSE;
      }	
      break;
      
    case C2:    // In the C2 state:
      if (key==CORRECT3){
	state=C3;
	door_open=FALSE;
      }else{
	state=START;
	door_open=FALSE;
      }	
      break;
      
    case C3:
      if (key==CORRECT4){
	state=START;
	door_open=TRUE;
	printf("*** Door open. ***\n");
      }else{
	state=START;
	door_open=FALSE;
      }	
      break;
      
    } // END switch (state){
    
    
    
    printf("Input=%d, ", key);
    if (door_open==TRUE){
      printf ("Open = True\n");
    }else{
      printf ("Open = False\n");
    }
    
    printf ("\n\n");
    
    
  } // END while(door_open==FALSE)
  
} // END main()

