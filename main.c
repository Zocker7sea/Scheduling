
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "core.h"
#include "processcontrol.h"


/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
unsigned systemTime = 0; 	// the current system time (up time)
void removeBlockedTest() {
	printf("\n -------------\n");
	addBlocked(0, 5);		// 55       2
	addBlocked(1, 20);		// 70       3
	addBlocked(2, 30);		//80        4
	addBlocked(3, 0);		//50        1
	//printf("\n\n  ReadyOne aka first one pid is %d\n\n", headOfBlockedList()->pid);// pid 3
	//removeBlocked(headOfBlockedList()->pid);
	printf("\n\t  first unlock pid is %d\n", blockedList->pid);
	//printf("\n\t  second unlock pid is %d\n", blockedList->next->pid);
	//printf("\n\t  thrid unlock pid is %d\n", blockedList->next->next->pid);
	//printf("\n\t  fourth unlock pid is %d\n", blockedList->next->next->next->pid);
	removeBlocked(headOfBlockedList()->pid);
	printf("\n_____________________________________________________\n");
	//printf("\n\t  first unlock pid is %d\n", blockedList->pid);
	//printf("\n\t  second unlock pid is %d\n", blockedList->next->pid);
	//printf("\n\t  thrid unlock pid is %d\n", blockedList->next->next->pid);
	printf("\n\n  ReadyOne aka first one pid is %d\n\n", headOfBlockedList()->pid);
	removeBlocked(headOfBlockedList()->pid);
	printf("\n\n  ReadyOne aka first one pid is %d\n\n", headOfBlockedList()->pid);
}
void blockedTest() {
	printf("\n -------------\n");
	printf("\nblockedTest\n");
	//if (isBlockedListEmpty()) {
	//	printf("empty\n\n\n");
	//}
	//else {
	//	printf("not empty\n\n\n");
	//}
	addBlocked(0, 5);		// 5        2
	addBlocked(1, 20);		// 20       3
	addBlocked(2, 30);		// 30       4
	addBlocked(3, 0);		// 00       1
	//printf("after addBlocked\n");
	
	printf("first unlock pid is %d\n", blockedList->pid);
	//printf("first unlock io is %d\n", blockedList->IOready);
	printf("second unlock pid is %d\n", blockedList->next->pid);
	//printf("second unlock io is %d\n", blockedList->next->IOready);
	printf("thrid unlock pid is %d\n", blockedList->next->next->pid);
	//printf("thrid unlock io is %d\n", blockedList->next->next->IOready);
	printf("fourth unlock pid is %d\n", blockedList->next->next->next->pid);
	//printf("fourth unlock io is %d\n", blockedList->next->next->next->IOready);
	//printf("\nBlockedOne aka first one pid is %d\n", headOfBlockedList()->pid);// pid 3

}
void readyTest() {
	printf("\n -------------\n");
	//if (isReadyListEmpty()) {
	//	printf("empty\n\n\n");
	//}
	//else {
	//	printf("not empty\n\n\n");
	//}
	addReady(0);		// 1      
	addReady(1);		// 2      
	addReady(2);		//3       
	addReady(3);		//4  
	/*if (isReadyListEmpty()) {
		printf("empty\n\n\n");
	}
	else {
		printf("not empty\n\n\n");
	}*/  
	printf("\n\nReadyOne aka first one pid is %d\n\n", headOfReadyList()->pid);// pid 0
	printf("\n		 first ready pid is %d\n", readyList->pid);
	printf("		 second ready pid is %d\n", readyList->next->pid);
	printf("		 thrid ready pid is %d\n", readyList->next->next->pid);
	removeReady(0);
	printf("\nReadyOne aka first one pid is %d\n", headOfReadyList()->pid);// pid 0
	
	//printf("============");
	//printf("\nReadyOne aka first one pid is %d\n", headOfReadyList()->pid);
	//printf("\Shedule pid is % d\n", schedule(readyList));
	//printf("\nReadyOne aka first one pid is %d\n", headOfReadyList()->pid);
}
void removeReadyTest() {
	printf("\n -------------\n");
	addReady(0);		// 1      
	addReady(1);		// 2      
	addReady(2);		//3       
	addReady(3);		//4  
	printf("\n\nReadyOne aka first one pid is %d\n\n", headOfReadyList()->pid);// pid 0
	//removeReady(headOfReadyList()->pid);
	printf("first ready pid is %d\n", readyList->pid);
	printf("second ready pid is %d\n", readyList->next->pid);
	printf("thrid ready pid is %d\n", readyList->next->next->pid);
	removeReady(0);
	removeReady(4);
	printf("first ready pid is %d\n", readyList->pid);
	printf("second ready pid is %d\n", readyList->next->pid);
	//printf("thrid ready pid is %d\n", readyList->next->next->pid);
	printf("\nReadyOne aka first one pid is %d\n", headOfReadyList()->pid);// pid 1
}
void headOfReady() {
	printf("\n -------------\n");
	addReady(1);
	addReady(22);
	addReady(12);
	removeReady(headOfReadyList(readyList)->pid);
	printf("\n\tfirst pid %d\n", headOfReadyList(readyList)->pid);
}
void shedule() {
	printf("\n -------------\n");
	addReady(0);
	addReady(1);
	//printf("\n\nfirst pid %d\n\n",headOfReadyList()->pid);
	schedule(readyList);
	//printf("\n\nfirst pid %d\n\n", headOfReadyList()->pid);
	//schedule(readyList);
	printf("\n\nfirst pid %d\n\n", headOfReadyList()->pid);
}
void removeList() {
	printf("\n -------------\n");
	addReady(1);
	addReady(2);
	
	printf("next head %d\n", headOfReadyList()->pid);
	if (headOfReadyList()->next != NULL) {
		printf("next");
	}
	else
	{
		printf("is nULL");
	}
		
	//printf(next);
}
void tests() {
		initOS();
		//removeBlockedTest();
		//blockedTest();
		//removeList();
		//shedule();
		readyTest();
		//removeReadyTest();
		//headOfReady();
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
	//-------------TestAREA ---------------------------
		//tests();
	return 1; 
}