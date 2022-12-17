/* Implementation of the scheduler */
/* for comments on the functions see the associated .h-file */

/* ----------------------------------------------------------------- */
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "scheduler.h"
#include "processcontrol.h"


/* ----------------------------------------------------------------- */
/*                Declarations of local helper functions             */



/* ----------------------------------------------------------------- */
/*                Externally available functions                     */
/* ----------------------------------------------------------------- */

pid_t schedule(readyList_t readyListParam)
{
	pid_t nextToRun;
	if (readyListParam == NULL) return NO_PROCESS;
	// get process from readylist
	nextToRun = headOfReadyList(readyListParam)->pid;


	// remove selected process from ready list
	//oder löst man dies, in dem man nur die rL auf rL.next setzt?
	removeReady(nextToRun);//hier die funktion aus processcontrol benutzen,
	printf("\n delete %d from readyList \n", nextToRun);
	//printf("delete %d from readyList \n", nextToRun);
	//printf("delete %d from readyList \n", nextToRun);
	return nextToRun;
	//old
		//pid_t nextToRun;
		//if (readyListParam == NULL) return NO_PROCESS;
		// get process from readylist
		//nextToRun = readyListParam->pid;
		// remove selected process from ready list	
		//readyList = NULL;			// for batch only one process can be in readylist 
		// -> simply delete entire list
		//return nextToRun;
}
	
/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */




