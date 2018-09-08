#ifndef MENU_H
#define MENU_H

/**
 * Function runs the command loop.    
 * @param Pre-loaded tree containing rules.
 */
void commandLoop(Tree *commands);

/**
 * Function displays command loop prompt.    
 */
void prompt(); 

/**
* Function removes hard return character at the end of a string.
* @param String to modify. 
*/
void removeTrailingHardReturn(char line[]); 

/**
* Function opens the file. 
* @param String argument filenmane from command line.
* @return File pointer to opened file.
*/
FILE* openFile (char *toOpen); 

/**
* Function loads the tree with the rules. 
* @param Tree structure to load.
* @param File pointer to opened file.
*/
void loadTree (Tree * a, FILE *in);

/**
* Function to make all characters in a string lower case. 
* @param String to modify. 
*/
void makeLowerCase(char *string);

/**
* Function asks user for a word from stdin, creates a rule and adds it to the tree.
* @param Tree structure with pre-loaded rules. 
*/
void addNewRule (); 

/**
 * Function gets double input from user and checks if double variable was loaded.
 * @return Double from stdin on success, -1 on failure.     
 */
double checkDouble (); 

/**
* Function removes a rule from the tree
* @param Tree structure with pre-loaded dictionary. 
*/
void removeRule (Tree *commands); 

/**
* Function updates previous rules' user rating.
* @param Tree structure with pre-loaded dictionary. 
*/
void update (Tree *commands); 

/**
* Function lets user have a discussion with the personal assistant.
* @param Tree structure with pre-loaded dictionary. 
*/
void discuss (Tree *commands); 

#endif
