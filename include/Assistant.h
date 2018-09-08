#ifndef ASSISTANT_H
#define ASSISTANT_H

typedef struct assistant {

	char *keyword;
	char *response;
	double userRating;
	double systemRating;
	int occurrences; 
	double learningRate; 

} Assistant;

/**
 * User defined function to print Assistant struct data. 
 * @param data to be printed.  
 */
void printFunction (void *data);

/**
 * User defined function to compare Assistant struct data. 
 * @param first data for comparison. 
 * @param second data for comparison.
 * @retun 0 if they are the same, 1 if a is greater than b, -1 otherwise. 
 */
int compareFunction (const void *a, const void *b); 

/**
 * User defined function to free data in Assistant struct. 
 * @param data to be freed.  
 */
void deleteFunction (void *data);

/**
 * Function to create new rule and initialize values.  
 * @param Keyword to assign. 
 * @param Response to assign.
 * @param User rating to assign.
 * @return newly made Assistant struct.
 */
Assistant *createRule (char *k, char *resp, double ur);

/**
 * Function to set user rating. 
 * @param New rating to assign.
 * @param Assistant struct to modify.
 */
void setUserRating(double rating, Assistant *a);

/**
 * Function gets user rating.  
 * @param Assistant struct to get userRating.
 * @return double User rating corresponding to Assistant struct given.
 */
double getUserRating(Assistant *a);

#endif
