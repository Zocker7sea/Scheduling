/* Functions for control and administration of processes including  */
/* creation, destruction, blocked-control...						*/
/* for comments on the functions see the associated .h-file 		*/

/* ----------------------------------------------------------------	*/
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "processcontrol.h"
#include "simruntime.h"

/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
PCB_t processTable[NUM_PROCESSES+1]; 	// the process table
readyList_t readyList;	// list of runnable processes ---> rL
readyList_t helperReadyList;
readyList_t readyNew;
blockedList_t blockedList;	// pointer to blocked process ---> bL
blockedList_t helperBlockedList;
blockedList_t blockedNew;

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/
blockedListElement_t blockedOne; // the only process that can be blocked 
/*this must be extended to a suitable data structure for multiprogramming */
readyListElement_t readyOne;	// the only process ready in the batch system 
/*this must be extended to a suitable data structure for multiprogramming */



/* ---------------------------------------------------------------- */
/* Functions for administration of processes in general 			*/
/* ---------------------------------------------------------------- */

pid_t getNextPid()
/* Typically the PID is the index into the process table, thus the pool  	*/
/* for PIDs is limited by the size of the process table. If the end of the	*/
/* process table is reached, new PIDs are assigned by re-using unused 		*/
/* entries in the process table. 											*/
/* If no new PID can be returned (i.e. the process table is full, zero is 	*/
/* returned, which is not a valid PID. 										*/

{
	static unsigned pidCounter = 0;
	// determine next available pid. 
	for (int i = 0; i < NUM_PROCESSES; i++) {
		pidCounter++; 
		if (pidCounter > NUM_PROCESSES) pidCounter = 1; 
		if (!processTable[pidCounter].valid) return pidCounter;
	}
	/* If the loop is completed there was no free entry in the process table */
	return 0;	/* not a valid PID indicating an error  */
}

Boolean deleteProcess(pid_t pid)
/* Voids the PCB of the process with the given pid, this includes setting 	*/
/* the valid-flag to invalid and setting other values to invalid values.	*/
/* retuns FALSE on error and TRUE on success								*/
{
	if (pid == NO_PROCESS)
		return FALSE;
	else {	/* PCB correctly passed, now delete it */
		processTable[pid].valid = FALSE;
		processTable[pid].pid = 0;
		processTable[pid].ppid = 0;
		processTable[pid].ownerID = 0;
		processTable[pid].start = 0;
		processTable[pid].duration = 0;
		processTable[pid].usedCPU = 0;
		processTable[pid].type = os;
		processTable[pid].status = ended;
		return TRUE;
	}
}

/* ---------------------------------------------------------------- */
/* Functions for administration of blocked processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process												*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/


Boolean initBlockedList(void)
/* Initialise the blocked process control data structure					*/
/* (no blocked processes exist at initialisation time of the os)			*/
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process												*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
{
	helperBlockedList = NULL;
	blockedNew = NULL;
	blockedList = NULL;
	blockedOne;
	return TRUE;
}

Boolean addBlocked(pid_t pid, unsigned blockDuration)
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process	(handled by the simulation)					*/
/*        calculated as the systemTime + blockDuration						*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/

/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
/* retuns FALSE on error and TRUE on success								*/
{
	processTable[pid].status = blocked;	// change process state to "blocked"

	blockedNew = malloc(sizeof(blockedList_t));
	blockedNew->pid = pid;
	blockedNew->IOready = systemTime + blockDuration;
	blockedNew->next = NULL;
	

	if (blockedList == NULL
		|| blockedList->IOready >= blockedNew->IOready){ //|| helperReadyList->pid >= pid)
		//  50 + 10 >= 50 + 5
		//guckt nach ob die liste leer ist oder ob die IOR 
		//vom listen element > als die neue IOR ist
		blockedNew->next = blockedList;
		//blockedNew next auf die bL setzten
		blockedList = blockedNew;
	}
	else {
		helperBlockedList = blockedList;
		//wenn die bL schon n viele einträge hat, zum ende der liste gehen und einen neuen eintrag erstellen
		while (helperBlockedList->next != NULL 
			&& helperBlockedList->next->IOready
			< blockedNew->IOready) {
			//gucken ob die hBL noch next einträge hat &&
			// ob dann die IOR < als die blockedNew->IOR ist 
			helperBlockedList = helperBlockedList->next;
			//an das ende der liste gehen
		}
		blockedNew->next = helperBlockedList->next;
		helperBlockedList->next = blockedNew;
		//old
			//blockedOne.IOready = systemTime + blockDuration;
			//  // this must be supported by an extended implementation!
			//blockedOne.pid = pid;
			//blockedOne.next = blockedList;
			//blockedList = &blockedOne;// remember the blocked process
	}
	return TRUE;
}

Boolean removeBlocked(pid_t pid)
/* Removes the given PID from the blocked-list								*/		
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
{
	//bisher gedacht, das er anfang der liste der erste eintrag ist, der verschwindet

	blockedList->pid = NO_PROCESS;//forget the blocked process hier den head der liste nehmen
	blockedList->IOready = 0; //da prozess dann ready wird ioR = 0
	blockedList = blockedList->next;//die blockedList auf den nächsten eintrag setzten
	//old
		//blockedOne.IOready = 0;
		//blockedOne.pid = NO_PROCESS;	// forget the blocked process
		//blockedList = NULL;				// now there is no blocked process
	return TRUE;
}

Boolean isBlockedListEmpty(void)
/* predicate returning TRUE if any blocked process exists, FALSE if no		*/
/* blocked processes exist													*/
{
	return (blockedList == NULL);
}

blockedListElement_t *headOfBlockedList()
/* returns a pointer to the first element of the blocked list				*/
/* MUST be implemented for simulation purposes								*/			
{
	//bisher, der erste eintrag ist, der erste welcher verschindet/ kürzeste IOtime
	if (!isBlockedListEmpty()) {
		
		blockedOne.pid = blockedList->pid;//weise rO pid die pid von rL zu 
		blockedOne.IOready = blockedList->IOready;//vom ersten eintrag, die IO zeit
		blockedOne.next = NULL;//null oder verweis auf next von bL
		return &blockedOne;	// return pointer to the only blocked element remembered
	} 
	else return NULL;		// empty blocked list has no first element
}


/* ---------------------------------------------------------------- */
/* Functions for administration of ready processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- The ready list is sorted by not decreasing start-times			*/
/*			(i.e. first process to become ready is always head of the list	*/
/*      															*/

Boolean initReadyList(void)
/* Initialise the ready process control data structure						*/
/* (no ready processes exist at initialisation time of the os)				*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the ready process in        xxxx */
/* xxxx batch processing. A ready list needs to be implemented 		   xxxx */
{
	helperReadyList = NULL;
	readyNew = NULL;
	readyList = NULL;
	readyOne;
	return TRUE;
}

Boolean addReady(pid_t pid)	// add this process to the ready list
/* retuns FALSE on error and TRUE on success								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the only ready process in   xxxx */
/* xxxx batch processing. A blocked list needs to be implemented 	   xxxx */
{
	processTable[pid].status = ready;// change process state to "ready"

	readyNew = malloc(sizeof(readyList_t));
	readyNew->pid = pid;
	readyNew->next = NULL;

	if (readyList == NULL) {
		readyNew->next = readyList;
		readyList = readyNew;
	}
	else {
		helperReadyList = readyList;
		//Ein Element an das Ende der Liste hinzufügen
		while (helperReadyList->next != NULL) {
			helperReadyList = helperReadyList->next;
			//an das ende der liste gehen
		}
		//wenn ende erreicht, einen neuen eintrag machen
		readyNew->next = helperReadyList->next;
		helperReadyList->next = readyNew;

		//old
			//readyOne.pid = pid; // speichter pid in readyOne.pid
			//readyOne.next = readyList;//hier next auf die liste setzen
			//readyList = &readyOne;?? muss man das dann auch verändern?
			
	}
		return TRUE;
}

Boolean removeReady(pid_t pid)
/* retuns FALSE on error and TRUE on success								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store ready process in batch    xxxx */
/* xxxx processing. A ready list needs to be implemented 		       xxxx */
{
	//löscht den ersten eintrag, aus der ready list, welcher dann bearbeitet wird oder?
	readyList->pid = NO_PROCESS;// forget the ready process hier den head der liste nehmen
	//oder mit head of lösen?
	//headOfReadyList()->pid = NO_PROCESS;
	//readyList = headOfReadyList()->next;
	readyList = readyList->next;//die readyliste auf den nächsten eintrag setzten
	//old
		//readyOne.pid = NO_PROCESS;// forget the ready process
		//readyList = readyOne.next; //hier die readyliste auf das next element setzen				
		// ----------now there is no ready process
	return TRUE;
}

Boolean isReadyListEmpty(void)
/* predicate returning TRUE if any ready process exists, FALSE if no		*/
/* ready processes exist													*/
{
	return (readyList == NULL);
}

readyListElement_t* headOfReadyList()
/* returns a pointer to the first element of the ready list				*/
/* MUST be implemented for simulation purposes								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
{
	if (!isReadyListEmpty()) {
		readyOne.pid = readyList->pid;//weise rO pid die pid von rL zu 
		readyOne.next = NULL;//NUll oder readyList->next??
		return &readyOne;	//erstes  listen element wird wiedergegeben
		// return pointer to the only ready element remembered
	}
	else return NULL;		// empty ready list has no first element
}

