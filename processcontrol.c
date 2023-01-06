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
readyList_t readyList;	// list of runnable processes
blockedList_t blockedList;	// list of all blocked processes
/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/




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
	blockedList = NULL;
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
	blockedList_t newBlocked = malloc(sizeof(blockedList_t));
	//speicher platz zuweisen
	if (newBlocked != NULL) {
		//wenn das zuweisen funktioniert hat, werte zuweisen
		newBlocked->pid = pid;
		newBlocked->IOready = systemTime + blockDuration;
		newBlocked->next = NULL;
	}
	//gucken ob die list leer ist oder ob die erste IO Time größer als die neue Io Time ist
	if (blockedList == NULL || blockedList->IOready >= newBlocked->IOready) {
		//vom neuen eintrag das Next auf den anfang der Liste setzen
		newBlocked->next = blockedList;
		//blockedlist neu belegen
		blockedList = newBlocked;
	}
	else {
		blockedList_t current = blockedList;
		//iterations variable
		while (current->next != NULL && current->next->IOready < newBlocked->IOready) {
			//überprüfen ob das current element nicht Null ist und ob 
			//die nächste IO Time kleiner als die neue Io Time ist
			current = current->next;
			//current auf das nächste Element setzten
		}
		//Next vom neuen Element auf den current next eintrag setzen
		newBlocked->next = current->next;
		//current next auf das neue element setzen
		current->next = newBlocked;
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
	//helfer list fürs iterieren
	blockedList_t current = blockedList;
	//zum speichern des vorherigen elements
	blockedList_t prev = NULL;
	//überprüfen ob das current element nicht NUll ist und die pid nicht mit der angegebenen pid übereinstimmt
	while (current != NULL && current->pid != pid) {
		//prev auf den derzeitigen current eintrag setzen
		prev = current;
		//current auf das nächste  element setzen
		current = current->next;
	}
	//wenn curren gleich Null ist 
	if (current == NULL) {
		//gibt es nichts zu löschen
		return FALSE;
	}
	//wenn prev gleich Null ist
	if (prev == NULL) {
		//ist es der erste eintrag und die blockedlist wird auf das current next element gesetzt
		blockedList = current->next;
	}
	//wenn prev ungleich NUll ist
	else {
		//next von prev auf current next setzten
		prev->next = current->next;
		//den speicher von current frei geben
		free(current);
	}
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
	if (!isBlockedListEmpty()) {
		return blockedList;	// return pointer to the only blocked element remembered
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
	readyList = NULL;
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
	//speicher platz zuweisen
	readyList_t newReady = malloc(sizeof(readyList_t));
	//wenn das zuweisen funktioniert hat, werte zuweisen
	if (newReady != NULL) {
		// werte  zuweisen
		newReady->pid = pid;
		newReady->next = NULL;
	}

	if (readyList == NULL) {
		//wenn die liste leer ist, dann wird die liste zu newReady
		readyList = newReady;
		return TRUE;
	}else {
		//helfer list fürs iterieren
		readyList_t current   = readyList;
		while (current->next != NULL) {
			//gucken ob das next element von current nicht Null ist
			current = current->next;
			//current auf den next wert setzten
		}
		//wenn der current next eintrag NUll ist, newReady ranhängen
		current->next = newReady;
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
	//helfer list fürs iterieren
	readyList_t current = readyList;
	//zum speichern des vorherigen elements
	readyList_t prev = NULL;
	//überprüfen ob das current element nicht NUll ist und die pid nicht mit der angegebenen pid übereinstimmt
	while (current != NULL && current->pid != pid) {
		//prev auf den derzeitigen current eintrag setzen
		prev = current;
		//current auf das nächste  element setzen
		current = current->next;
	}
	//wenn curren gleich Null ist 
	if (current == NULL) {
		//gibt es nichts zu löschen
		return FALSE;
	}
	//wenn prev gleich Null ist
	if (prev == NULL) {
		//ist es der erste eintrag und die readylist wird auf das current next element gesetzt
		readyList = current->next;
	}
	//wenn prev ungleich NUll ist
	else {
		//next von prev auf current next setzten
		prev->next = current->next;
		//den speicher von current frei geben
		free(current);
	}
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
		return readyList;	//erstes  listen element wird wiedergegeben
	}
	else return NULL;		// empty ready list has no first element
}

