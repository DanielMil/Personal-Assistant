#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../include/Assistant.h"
#include "../include/TreeAPI.h"
#include "../include/menu.h"

#define MAX_FILENAME_LENGTH 80
#define MAX_WORD_LENGTH 46
#define MAX_WORDS_IN_SENTENCE 50

void commandLoop(Tree *commands) {

	char selection[50];

	while (1) {

		prompt();
		printf("------------------\nChoice: ");
		fgets(selection, 50, stdin);
		removeTrailingHardReturn(selection);

		if (selection[0] == '1') {
			
			addNewRule(commands); 

		} else if (selection[0] == '2') {

			removeRule(commands); 
			
		} else if (selection[0] == '3') {
			
			printf("The current rules stored are:\n");
			printInOrder(commands, &printFunction);
			printf("\n");

		} else if (selection[0] == '4') {

			update(commands); 

		} else if (selection[0] == '5') {

			discuss(commands); 

		} else if (selection[0] == '9') {

			return; 

		} else {

			printf("Invalid input, please try again.\n");

		}

	}

}

FILE* openFile (char *toOpen) {

	char fileName[MAX_FILENAME_LENGTH];
	FILE* savePtr;
	savePtr = fopen(toOpen, "r");

	while (savePtr == NULL) {

		printf("File could not open\nPlease input another filename:\n");
		fgets(fileName, MAX_FILENAME_LENGTH, stdin);
		removeTrailingHardReturn(fileName);

		savePtr = fopen(fileName, "r");
	}

	return savePtr;
}

void loadTree (Tree * a, FILE *in) {

	char *word;
	char *sentence;
	char tempBuffer[80];
	int length;
	int lineCount = 1; 
	int counter = 0; 

	while (fgets(tempBuffer, 80, in) != NULL) {
		removeTrailingHardReturn(tempBuffer);
		length = strlen(tempBuffer);
		makeLowerCase(tempBuffer);

		if (lineCount % 2 == 1) {
			word = malloc(sizeof(char) * (length+1));
			strcpy(word, tempBuffer);
		} else {
			sentence = malloc(sizeof(char) * (length+1));
			strcpy(sentence, tempBuffer);
		}

		counter++; 

		if (counter == 2) {
			Assistant *newRule = createRule(word, sentence, 0.5);
			addToTree(a, newRule); 
			counter = 0; 
		}

		lineCount++;
	}
}

void makeLowerCase(char *string) {

	int i = 0;

	for (i = 0; i < strlen(string); i++) {
		string[i] = tolower(string[i]);
	}

}

void addNewRule (Tree *commands) {

	char temp[MAX_WORD_LENGTH];
	char *toAddKey;
	char *toAddResponse;
	double toAddUserRating; 

	int currWords = commands->count; 

	printf("\nPlease enter a keyword to be added: ");

	fgets(temp, MAX_WORD_LENGTH, stdin);
	removeTrailingHardReturn(temp);
	makeLowerCase(temp);
	int length = strlen(temp);

	toAddKey = malloc(sizeof(char) * length);
	strcpy(toAddKey, temp);

	printf("\nPlease enter a response to be added: ");

	fgets(temp, MAX_WORD_LENGTH, stdin);
	removeTrailingHardReturn(temp);
	makeLowerCase(temp);
	length = strlen(temp);

	toAddResponse = malloc(sizeof(char) * length);
	strcpy(toAddResponse, temp);

	printf("\nPlease enter a user rating to be added: ");

	toAddUserRating = checkDouble();

	while (toAddUserRating == -1) {
		printf("Invalid rating.\nPlease enter another rating: "); 
		toAddUserRating = checkDouble();
	}

	Assistant *toAdd = createRule(toAddKey, toAddResponse, toAddUserRating); 
	addToTree(commands, toAdd); 

	if (currWords + 1 == commands->count) {
		printf("The word <%s> was successfully added to the tree.\n", toAddKey);
		printf("------------------\n\n");
	} else {
		printf("Error adding the word <%s> to the tree!\n", temp);
		printf("------------------\n\n");
	}
} 

double checkDouble () {

	double num; 

	if (scanf("%lf", &num) <= 0) {
		getchar(); 
		return -1;
	}

	if (num < 0 || num > 1)
		return -1;

	return num; 
}

void removeRule (Tree *commands) {

	char temp[MAX_WORD_LENGTH];
	int currWords = commands->count;

	printf("\nPlease enter a word to be removed: ");

	fgets(temp, MAX_WORD_LENGTH, stdin);
	removeTrailingHardReturn(temp);
	makeLowerCase(temp);

	Assistant *toRemove = createRule(temp, "", 0.5);

	removeFromTree(commands, toRemove);

	if (currWords - 1 == commands->count) {
		printf("The word <%s> was successfully removed from the tree.\n", temp);
		printf("------------------\n\n");
	} else {
		printf("Error removing the word <%s> from the tree!\n", temp);
		printf("------------------\n\n");
	}

}

void update (Tree *commands) {

	char temp[MAX_WORD_LENGTH];
	double toAddUserRating = 0; 

	printf("\nPlease enter a keyword corresponding to the rule to be updated: ");

	fgets(temp, MAX_WORD_LENGTH, stdin);
	removeTrailingHardReturn(temp);
	makeLowerCase(temp);

	Assistant *a = createRule(temp, "", 0.5);

	if (findInTree(commands, a) == NULL) {
		printf("Keyword not found.\n\n");
		return; 
	} else {
		a = (Assistant*)findInTree(commands, a);
		printf("The current rating is: %.2lf\n", getUserRating(a));
	}

	printf("Enter a new rating: ");

	toAddUserRating = checkDouble();

	while (toAddUserRating == -1) {
		printf("Invalid rating.\nPlease enter another rating: "); 
		toAddUserRating = checkDouble();
	}

	setUserRating(toAddUserRating, a); 
	printf("Rating successfully updated.\n\n");
}

void discuss (Tree *commands) {

	char temp[MAX_WORD_LENGTH];
	char *splitArray[MAX_WORDS_IN_SENTENCE];
	int i = 0, j = 0; 
	char toPrintKeyword[MAX_WORD_LENGTH] = ""; 
	int found = 0; 
	double currentMaxSum = 0; 

	printf("\nUser: ");
	fgets(temp, MAX_WORD_LENGTH, stdin);
	removeTrailingHardReturn(temp);
	makeLowerCase(temp); 

	if (strlen(temp) == 0) {
		printf("Question cannot be empty.\n");
		return;
	}

	if (temp[strlen(temp) - 1] == '?' || temp[strlen(temp) - 1] == '.' || temp[strlen(temp) - 1] == '!') {
		temp[strlen(temp) - 1] = '\0';
	}

	char *p = strtok(temp, " ");

	while (p != NULL) {
		splitArray[i++] = p;
		p = strtok(NULL, " ");
	}

	for (j = 0; j < i; j++) {

		Assistant *a = createRule(splitArray[j], "", 0.5);

		if (findInTree(commands, a) != NULL) {
			found = 1;
			a = (Assistant*)findInTree(commands, a);

			if ((a->systemRating + a->userRating) > currentMaxSum) {
				currentMaxSum = a->systemRating + a->userRating; 
				strcpy(toPrintKeyword, a->keyword); 
			}
		} 
	
	}

	Assistant *b = createRule(toPrintKeyword, "", 0.5);
	b = (Assistant*)findInTree(commands, b);

	if (found == 0) {
		printf("Personal Assistant: I'm unfamiliar with that phrase.\n\n");
		return; 
	} else {	
		printf("Personal Assistant: %s\n", b->response);
	}

	printf("Personal Assistant: Was this feedback helpful? 'y' or 'n': ");

	fgets(temp, MAX_WORD_LENGTH, stdin);
	removeTrailingHardReturn(temp);
	makeLowerCase(temp); 
	
	while (temp[0] != 'y' && temp[0] != 'n') {
		printf("Personal Assistant: Invalid response. Please let me know if I was helpful: ");
		fgets(temp, MAX_WORD_LENGTH, stdin);
		removeTrailingHardReturn(temp);
		makeLowerCase(temp);
	}

	b->occurrences++; 

	if (temp[0] == 'y') {
		b->systemRating = b->systemRating + ((b->systemRating * b->learningRate) / b->occurrences);
	} else {
		b->systemRating = b->systemRating - ((b->systemRating * b->learningRate) / b->occurrences);
	}

	printf("\n");
}

void prompt () {

	printf("Enter 1 to add a new rule.\nEnter 2 to remove a rule.\nEnter 3 to display rules.\nEnter 4 to modify rule rating.\nEnter 5 to discuss.\nEnter 9 to quit\n");
}

void removeTrailingHardReturn(char line[]) {

	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
}

