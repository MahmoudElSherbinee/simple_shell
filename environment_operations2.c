#include "shell.h"

/**
 * setEnvironmentVariable - function sets or updates an environment variable.
 *
 * This function sets or updates an environment variable in the linked list of
 * environment variables ('information->environment_list').
 * It first checks if the input parameters 'variable' and 'value' are not NULL.
 * It then allocates memory for a new string buffer, concatenates the variable
 * and its value with an equal sign, and checks if the
 * variable already exists in the linked list.
 * If the variable exists, it updates its value; otherwise,
 * it adds a new node to the end of the linked list.
 * The 'information->environment_modified' flag is set to indicate
 * that the environment has been modified.
 *
 * @information: A pointer to the structure containing environment variables.
 * @variable: The name of the environment variable to set or update.
 * @value: The value to set for the environment variable.
 *
 * Return: Returns 0 if successful, 1 if memory allocation fails.
 */
int setEnvironmentVariable(CommandInfo *information,
						   char *variable, char *value)
{
	char *buffer = NULL;

	StringList *currentNode;
	char *substringStart;

	/* Step 1: Check if 'variable' and 'value' are not NULL */
	if (!variable || !value)
		return (0);

	/* Step 2: Allocate memory for a new string buffer */
	buffer = malloc(str_length(variable) + str_length(value) + 2);
	if (!buffer)
		return (1);

	/* Step 3: Concatenate the variable and its value with an equal sign */
	str_copy(buffer, variable);
	str_concatenate(buffer, "=");
	str_concatenate(buffer, value);

	/* Step 4: Traverse the linked list to check if the variable already exists */
	currentNode = information->environment_list;
	while (currentNode)
	{
		substringStart = checkIfPrefix(currentNode->string, variable);
		if (substringStart && *substringStart == '=')
		{
			/* Step 5: Update the value if the variable already exists */
			free(currentNode->string);
			currentNode->string = buffer;
			information->environment_modified = 1;
			return (0);
		}
		currentNode = currentNode->next;
	}
	/* Step 6: Add a new node to the end of the linked list */
	addNodeToEndOfList(&(information->environment_list), buffer, 0);
	free(buffer);
	information->environment_modified = 1;
	/* Step 7: Return 0 */
	return (0);
}

/**
 * unsetEnvironmentVariable - function sets or updates an environment variable.
 *
 * This function sets or updates an environment variable in the linked list of
 * environment variables ('information->environment_list').
 * It first checks if the input parameters
 * 'variable' and 'value' are not NULL.
 * It then allocates memory for a new string buffer,
 * concatenates the variable and its value with an equal sign,
 * and checks if the variable already exists in the linked list.
 * If the variable exists, it updates its value; otherwise,
 * it adds a new node to the end of the linked list.
 * The 'information->environment_modified' flag is set to
 * indicate that the environment has been modified.
 *
 * @information: A pointer to the structure containing environment variables.
 * @variable: The name of the environment variable to set or update.
 *
 * Return: Returns 0 if successful, 1 if memory allocation fails.
 */

int unsetEnvironmentVariable(CommandInfo *information, char *variable)
{
	StringList *currentNode = information->environment_list;
	size_t index = 0;
	char *substringStart;

	/* Step 1: Check if 'information->environment_list' or 'variable' is NULL */
	if (!currentNode || !variable)
		return (0);

	/* Step2 Iterate through the linked list to find and remove matching nodes */
	while (currentNode)
	{
		substringStart = checkIfPrefix(currentNode->string, variable);
		if (substringStart && *substringStart == '=')
		{
			/* Step 3: Delete the node if the variable name matches */
			information->environment_modified =
				deleteNodeAtIndexInList(&(information->environment_list), index);
			index = 0;
			currentNode = information->environment_list;
			continue;
		}
		currentNode = currentNode->next;
		index++;
	}

	/* Step 4: Return whether the environment was modified (1) or not (0) */
	return (information->environment_modified);
}

/**
 * SetCustomEnvironment - function sets a custom environment variable
 * using the provided information.
 *
 * This function checks the argument count and calls a custom setenv function.
 * If the number of arguments is not 3, an error message is printed, and the
 * function returns 1.
 * If setenv is successful, the function returns 0; otherwise, it returns 1.
 *
 * @customInfo: A pointer to the information structure containing arguments.
 *
 * Return: Returns 0 on success, 1 on failure.
 */
int SetCustomEnvironment(CommandInfo *customInfo)
{
	/* Check if the number of arguments is not equal to 3. */
	if (customInfo->argument_count != 3)
	{
		/* Print an error message for incorrect argument count. */
		error_print_str("Incorrect number of arguments\n");
		/* Return 1 to indicate an error. */
		return (1);
	}

	/* Call a custom setenv function with provided information. */
	if (setEnvironmentVariable(customInfo, customInfo->arguments_array[1],
							   customInfo->arguments_array[2]))
		/* Return 0 if setenv was successful. */
		return (0);

	/* Return 1 to indicate an error. */
	return (1);
}

/**
 * UnsetCustomEnvironment - function unsets custom environment variables
 * using the provided information.
 *
 * This function checks the argument count and unsets environment variables
 * accordingly. If the argument count is 1, an error message is printed, and
 * the function returns 1. Otherwise, it iterates through the arguments and
 * calls a custom unsetenv function for each variable. The function returns 0
 * on success.
 *
 * @customInfo: A pointer to the information structure containing arguments.
 *
 * Return: Returns 0 on success, 1 on failure.
 */
int UnsetCustomEnvironment(CommandInfo *customInfo)
{
	int i;
	/* Check if there are too few arguments. */
	if (customInfo->argument_count == 1)
	{
		/* Print an error message for too few arguments. */
		error_print_str("Too few arguments.\n");
		/* Return 1 to indicate an error. */
		return (1);
	}

	/* Iterate through the arguments and unset each environment variable. */
	for (i = 1; i <= customInfo->argument_count; i++)
		unsetEnvironmentVariable(customInfo, customInfo->arguments_array[i]);

	/* Return 0 to indicate success. */
	return (0);
}
