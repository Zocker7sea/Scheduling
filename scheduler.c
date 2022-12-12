/* Implementation of the scheduler */
/* for comments on the functions see the associated .h-file */

/* ----------------------------------------------------------------- */
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "scheduler.h"
//#include "processcontrol.h"


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
	nextToRun = readyListParam->pid;
	//da die frisch hinzugefügten prozesse an das ende gepackt werden,
	//  ist der prozess, welcher ausgeführt werden soll am anfang der list
	// 
	// 
	// remove selected process from ready list
	//removeReady(nextToRun);//hier die funktion aus processcontrol benutzen,
	//um einen  prozess aus der readyliste zu nehmen
	
	//readyList=NULL;			// for batch only one process can be in readylist 
							// -> simply delete entire list
	return nextToRun;
}
	
/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */




