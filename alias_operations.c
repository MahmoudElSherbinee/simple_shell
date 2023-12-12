#include "shell.h"
/**
* alias_unsetter - function unsets (removes) an command_alias by name.
*
* This function unsets (removes) an alias from the linked list of aliases
* ('information->command_alias') by name.
* It searches for the command_alias in the linked list based on
* the provided name ('string') and removes the corresponding node.
* The function returns 1 if the alias was successfully unset, and 0 otherwise.
*
* @information: A pointer to the structure containing aliases.
* @string: The name of the command_alias to unset.
*
* Return: Returns 1 if successful,
* 0 if the command_alias was not found or an error occurred.
*/
int alias_unsetter(CommandInfo *information, char *string)
{
	char *equal_sign, x;

	int result;

	StringList *aliasNode;

	/* Step 1: Find the equal sign in the command_alias string */
	equal_sign = char_in_str(string, '=');
	if (!equal_sign)
		return (1);

	/* Step 2: Temporarily set the equal sign to null-terminate the name */
	x = *equal_sign;
	*equal_sign = 0;

	/* Step 3: Get the index of the command_alias in the linked list */
	aliasNode = findNodeWithPrefix(information->command_alias, string, -1);
	result = deleteNodeAtIndexInList(&(information->command_alias),
									 getNodeIndexInList(information->command_alias,
														aliasNode));

	/* Step 4: Restore the original character and return the result */
	*equal_sign = x;

	return (result);
}

/**
* alias_setter - function sets or updates an command_alias.
*
* This function sets or updates an command_alias in the linked list of aliases
* ('information->command_alias').
* It first checks if the provided command_alias string ('string') contains
* an equal sign.
* If it does, the function checks if the string after the equal sign
* is empty and unsets the command_alias if true.
* If the string after the equal sign is not
* empty, the function first unsets the existing alias with the same name
* and then adds a new node to the end of the linked list
* with the provided command_alias string.
* The 'information->alias_changed' flag is set to indicate
* that the aliases have been modified.
*
* @information: A pointer to the structure containing aliases.
* @string: The command_alias string to set or update.
*
* Return: Returns 0 if successful, 1 if an error occurred.
*/
int alias_setter(CommandInfo *information, char *string)
{
	char *equal_sign;

	/* Step 1: Find the equal sign in the command_alias string */
	equal_sign = char_in_str(string, '=');
	if (!equal_sign)
		return (1);

	/* Step 2: Check if the string after the equal sign is empty */
	if (!*++equal_sign)
		return (alias_unsetter(information, string));

	/* Step 3: Unset the existing command_alias with the same name */
	alias_unsetter(information, string);

	/* Step 4: Add a new node to the end of the linked list */
	return (addNodeToEndOfList(&(information->command_alias), string, 0) == NULL);
}

/**
* alias_printer - function prints the alias information.
*
* This function prints the information of the specified alias node. It extracts
* the alias name and associated command from the node's string and prints them.
* The function returns 0 if successful, and 1 otherwise.
*
* @node: A pointer to the alias node.
*
* Return: Returns 0 if successful, 1 if the node is NULL.
*/
int alias_printer(StringList *node)
{
	char *equal_sign = NULL, *aliasName = NULL;

	/* Step 1: Check if the node is not NULL */
	if (node)
	{
		/* Step 2: Find the equal sign in the alias string */
		equal_sign = char_in_str(node->string, '=');

		/* Step 3: Print the alias name surrounded by single quotes */
		for (aliasName = node->string; aliasName <= equal_sign; aliasName++)
			print_char(*aliasName);
		print_char('\'');

		/* Step 4: Print the associated command */
		print_str(equal_sign + 1);
		print_str("'\n");

		/* Step 5: Return 0 */
		return (0);
	}

	/* Step 6: Return 1 if the node is NULL */
	return (1);
}

/**
* alias_custom - function displays or manages aliases.
*
* This function displays or manages aliases
* based on the command-line arguments.
* If called without arguments, it prints all existing aliases. If called with
* arguments in the form of 'alias_name=command', it sets or updates aliases.
* If an alias is specified without a command,
* it prints the command associated with that alias.
* The function returns 0 if successful.
*
* @information: A pointer to the structure containing aliases.
*
* Return: Returns 0 if successful.
*/
int alias_custom(CommandInfo *information)
{
	int i = 0;

	char *equal_sign = NULL;

	StringList *node = NULL;

	/* Step 1: Check if there are no arguments */
	if (information->argument_count == 1)
	{
		/* Step 2: Display all existing aliases */
		node = information->command_alias;
		while (node)
		{
			alias_printer(node);
			node = node->next;
		}
		return (0);
	}

	/* Step 3: Process arguments */
	for (i = 1; information->arguments_array[i]; i++)
	{
		equal_sign = char_in_str(information->arguments_array[i], '=');
		if (equal_sign)
			/* Step 4: Set or update aliases */
			alias_setter(information, information->arguments_array[i]);
		else
			/* Step 5: Print the command associated with the specified alias */
			alias_printer(findNodeWithPrefix(information->command_alias,
											 information->arguments_array[i], '='));
	}

	/* Step 6: Return 0 */
	return (0);
}

/**
* alias_replacer - function replaces alias in command arguments.
*
* This function replaces the specified alias in the command arguments. It looks
* for an alias matching the command name and replaces the command name with the
* associated command from the alias. The process is repeated up to 10 times to
* handle nested aliases. The function returns 1 if successful, and 0 otherwise.
*
* @information: A pointer to the structure containing aliases
* and command arguments.
*
* Return: Returns 1 if successful, 0 otherwise.
*/
int alias_replacer(CommandInfo *information)
{
	int i;

	StringList *node;
	char *equal_sign;

	/* Step 1: Iterate up to 10 times to handle nested aliases */
	for (i = 0; i < 10; i++)
	{
		/* Step 2: Find the alias node matching the command name */
		node = findNodeWithPrefix(information->command_alias,
														information->arguments_array[0], '=');

		/* Step 3: Return 0 if no matching alias is found */
		if (!node)
			return (0);

		/* Step 4: Free the current command name */
		free(information->arguments_array[0]);

		/* Step 5: Find the equal sign in the alias string */
		equal_sign = char_in_str(node->string, '=');

		/* Step 6: Duplicate the associated command from the alias */
		equal_sign = str_duplicate(equal_sign + 1);

		/* Step 7: Return 0 if the duplication fails */
		if (!equal_sign)
			return (0);

		/* Step 8: Update the command name in the arguments */
		information->arguments_array[0] = equal_sign;
	}

	/* Step 9: Return 1 if successful */
	return (1);
}
