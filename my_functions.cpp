#include "stdafx.h"
#include "my_functions.h"
#include "VoronoiDiagramGenerator.h"





double RandReal(int low, int high)
{
	if (0 == ourInitialized){   
		ourInitialized = 1;          // only call srand once
        srand(unsigned(time(0)));    
    }
	int lowest = low;
	int highest = high;
  
    int range=(highest-lowest)+1; 
	 
	return lowest+ range*rand()/(RAND_MAX + 1.0); 
}
