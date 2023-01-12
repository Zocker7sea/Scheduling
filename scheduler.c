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

pid_t schedule(readyList_t readyListParam){
	pid_t nextToRun;
	if (readyListParam == NULL) return NO_PROCESS;
	nextToRun = headOfReadyList()->pid; //nextToRun die pid des ersten Eintrags aus der Readylist zuweisen
	removeReady(nextToRun);//die Pid von nextToRun aus der Readylist l�schen, da dieser dann ausgef�hrt wird
	return nextToRun;
}
	
/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */




