#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TreeAPI.h"
#include "../include/Assistant.h"
#include "../include/menu.h"

int main (int argc, char **argv) {

	Tree *assistantTree = createBinTree(&compareFunction, &deleteFunction);
	FILE *fptr = openFile(argv[1]);  

	loadTree(assistantTree, fptr);
	commandLoop(assistantTree); 

	fclose(fptr);
	destroyBinTree(assistantTree); 

	return 0;
}
