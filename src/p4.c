#include <stdio.h>

int 
main(void) {
	
	int i;
	
	for(i = 0; i < 1000000; i++) {
		if (i == 0) 
			printf("running P4...\n");			
	}

	return 0;
}