#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Assistant.h"
#include "../include/TreeAPI.h"


Assistant *createRule (char *k, char *resp, double ur) {

	Assistant *newAssistant = malloc(sizeof(Assistant));

	newAssistant->keyword = k;
	newAssistant->response = resp; 
	newAssistant->userRating = ur;
	newAssistant->systemRating = 0.5;
	newAssistant->occurrences = 0;
	newAssistant->learningRate = 0.05; 

	return newAssistant; 
}

void printFunction (void *data) {

	Assistant *a = (Assistant*)data;

	printf("%s\tRating: %.2lf\tSystem: %.2lf\tOccurrences: %d\n", a->keyword, a->userRating, a->systemRating, a->occurrences);
}

int compareFunction (const void *a, const void *b) {

	Assistant *x = (Assistant*)a;
	Assistant *y = (Assistant*)b;

	return (strcmp(x->keyword, y->keyword)); 
}

void deleteFunction (void *data) {

	Assistant *a = (Assistant*)data;
	free(a->keyword);
	a->keyword = NULL;
	free(a->response);
	a->response = NULL;
	free(a);
	a = NULL; 
}

void setUserRating(double rating, Assistant *a) {

	a->userRating = rating; 
}

double getUserRating(Assistant *a) {

	return a->userRating; 
}


