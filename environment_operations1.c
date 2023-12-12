#include "shell.h"

/**
* getEnvironmentVariable - function
* retrieves the value of an environment variable.
*
* This function retrieves the value of an environment variable specified by
* the 'name' parameter from a linked list of environment variables.
* It iterates through the linked list and uses the 'starts_with' function to
* check if the current environment variable starts with the specified 'name'.
* If a match is found, it returns a pointer to the value of
* that environment variable. If no match is found, it returns NULL.
*
* @information: A pointer to the structure containing environment variables.
* @name: The name of the environment variable to retrieve.
*
* Return: Returns a pointer to the value of the environment variable or NULL.
*/
char *getEnvironmentVariable(CommandInfo *information, const char *name)
{
	StringList *currentNode = information->environment_list;
	char *substringStart;

	/* Step 1: Iterate through the linked list of environment variables */
	while (currentNode)
	{
		/*Check if the current environment variable starts with the specified name */
		substringStart = checkIfPrefix(currentNode->string, name);

		/* Step 3: Check if a match is found and the value is not empty */
		if (substringStart && *substringStart)
			return (substringStart);

		/* Step 4: Move to the next node in the linked list */
		currentNode = currentNode->next;
	}

	/* Step 5: Return NULL if no matching environment variable is found */
	return (NULL);
}

/**
* printEnvironmentVariables - function prints the contents
* of the environment variables.
*
* This function prints the contents of the environment variables stored in
* the 'information' structure.
* It uses the 'print_list_str' function to
* display the strings in the linked list.
*
* @information: A pointer to the structure containing environment variables.
*
* Return: Always returns 0.
*/
int printEnvironmentVariables(CommandInfo *information)
{
	/*Print the contents of the environment variables using 'print_list_str' */
	printLinkedListStrings(information->environment_list);

	/* Step 2: Return 0 */
	return (0);
}


/**
* populateEnvironmentList - function populates
* the environment variable linked list.
*
* This function populates the environment variable linked list
* in the 'information' structure with the contents of the 'environment' array.
* It iterates through the 'environment' array and
*adds each environment variable to the linked list using
* the 'add_node_end' function.
*
* @information: A pointer to the structure containing environment variables.
*
* Return: Always returns 0.
*/

int populateEnvironmentList(CommandInfo *information)
{
	/* Initialize a new linked list for environment variables */
	StringList *envList = NULL;
	size_t i;

	/* Step 1: Iterate through the 'environment' array */
	for (i = 0; environ[i]; i++)
	{
		/* Step 2: Add each environment variable to the linked list */
		addNodeToEndOfList(&envList, environ[i], 0);
	}

	/* Step 3: Assign the populated linked list */
	/* to the 'environment_list' field in the 'information' structure */
	information->environment_list = envList;

	/* Step 4: Return 0 */
	return (0);
}

/**
* getEnvironmentVariables - function retrieves or generates an array
* of strings representing environment variables.
*
* This function checks if the 'information->environment_variables'
* array is not already populated or if there has been a change in the
* environment variables ('information->environment_modified').
* If either condition is true, it updates 'information->environment_variables'
* by converting the linked list of environment variables
* ('information->environment_list') into an array of strings
* using the 'list_to_strings' function.
* The 'information->environment_modified' flag is then reset.
* Finally, the function returns the array of strings.
*
* @information: A pointer to the structure containing environment variables.
*
* Return: Returns the array of strings representing environment variables.
*/
char **getEnvironmentVariables(CommandInfo *information)
{
	/* Step 1: Check if 'information->environment_variables' */
	/* is not already populated or if there has been a change */
	if (!information->environment_variables || information->environment_modified)
	{
		/* Step 2: Update 'information->environment_variables' by */
		/* converting the linked list to an array of strings */
		information->environment_variables =
		convert_list_arrstr(information->environment_list);

		/* Step 3: Reset the 'information->environment_modified' flag */
		information->environment_modified = 0;
	}

	/* Step 4: Return the array of strings representing environment variables */
	return (information->environment_variables);
}
