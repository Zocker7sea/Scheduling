
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "core.h"
#include "processcontrol.h"


/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
unsigned systemTime = 0; 	// the current system time (up time)
void removeBlockedTest() {
	addBlocked(0, 5);		// 55       2
	addBlocked(1, 20);		// 70       3
	addBlocked(2, 30);		//80        4
	addBlocked(3, 0);		//50        1
	printf("\n\nReadyOne aka first one pid is %d\n\n", headOfBlockedList()->pid);// pid 3

	removeBlocked(headOfBlockedList);
	printf("first unlock pid is %d\n", blockedList->pid);
	printf("first unlock io is %d\n", blockedList->IOready);
	printf("second unlock pid is %d\n", blockedList->next->pid);
	printf("second unlock io is %d\n", blockedList->next->IOready);
	printf("thrid unlock pid is %d\n", blockedList->next->next->pid);
	printf("thrid unlock io is %d\n", blockedList->next->next->IOready);
	printf("\n\nReadyOne aka first one pid is %d\n\n", headOfBlockedList()->pid);// pid 3

}
void blockedTest() {
	if (isBlockedListEmpty()) {
		printf("empty\n\n\n");
	}
	else {
		printf("not empty\n\n\n");
	}
	addBlocked(0, 5);		// 55       2
	addBlocked(1, 20);		// 70      3
	addBlocked(2, 30);		//80       4
	addBlocked(3, 0);		//50        1
	printf("after addBlocked\n");
	if (isBlockedListEmpty()) {
	printf("empty\n\n\n");
}
	else {
		printf("not empty\n\n\n");
	}
	printf("first unlock pid is %d\n", blockedList->pid);
	printf("first unlock io is %d\n", blockedList->IOready);
	printf("second unlock pid is %d\n", blockedList->next->pid);
	printf("second unlock io is %d\n", blockedList->next->IOready);
	printf("thrid unlock pid is %d\n", blockedList->next->next->pid);
	printf("thrid unlock io is %d\n", blockedList->next->next->IOready);
	printf("fourth unlock pid is %d\n", blockedList->next->next->next->pid);
	printf("fourth unlock io is %d\n", blockedList->next->next->next->IOready);
	printf("\nBlockedOne aka first one pid is %d\n", headOfBlockedList()->pid);// pid 3

}
void readyTest() {
	if (isReadyListEmpty()) {
		printf("empty\n\n\n");
	}
	else {
		printf("not empty\n\n\n");
	}
	addReady(0);		// 1      
	addReady(1);		// 2      
	addReady(2);		//3       
	addReady(3);		//4  
	if (isReadyListEmpty()) {
		printf("empty\n\n\n");
	}
	else {
		printf("not empty\n\n\n");
	}
	printf("first ready pid is %d\n", readyList->pid);
	printf("second ready pid is %d\n", readyList->next->pid);
	printf("thrid ready pid is %d\n", readyList->next->next->pid);
	printf("fourth ready pid is %d\n", readyList->next->next->next->pid);
	printf("\nReadyOne aka first one pid is %d\n", headOfReadyList()->pid);// pid 0
}
void removeReadyTest() {
	addReady(0);		// 1      
	addReady(1);		// 2      
	addReady(2);		//3       
	addReady(3);		//4  
	printf("\n\nReadyOne aka first one pid is %d\n\n", headOfReadyList()->pid);// pid 0
	removeReady(headOfReadyList());
	printf("first ready pid is %d\n", readyList->pid);
	printf("second ready pid is %d\n", readyList->next->pid);
	printf("thrid ready pid is %d\n", readyList->next->next->pid);
	printf("\nReadyOne aka first one pid is %d\n", headOfReadyList()->pid);// pid 1
}

int main(int argc, char* argv[])
	



{	// starting point, all processing is done in called functions
	sim_initSim();		// initialise simulation run-time environment
	initOS();		// initialise operating system
	logGeneric("Starting stimulus-based simulation");
	coreLoop();		// start scheduling loop
	logGeneric("Simulation complete, shutting down");
	sim_closeSim();		// shut down simulation envoronment
	fflush(stdout);			// make sure the output on the console is complete 
	//-------------TestARE ---------------------------
		//blockedTest();
		//removeBlockedTest();
		//readyTest();
		//removeReadyTest();
	return 1; 
}