#include "shell.h"

/**
 * information_setter - function sts fields in the command
 * information structure based on provided arguments.
 *
 * This function populates various fields in the `information` structure,
 * such as the executable name, argument vector, and argument count.
 * It also performs replacements for aliases and variables if applicable.
 *
 * @information: Pointer to the command information structure.
 * @arguments:   Command-line arguments passed to the shell.
 */

void information_setter(CommandInfo *information, char **arguments)
{
	int argumentCount = 0;

	/* Step 1: Set the executable name. */
	information->file_name = arguments[0];

	/* Step 2: Process and set the argument vector. */
	if (information->argument)
	{
		/* Attempt to split the argument string into an argument vector. */
		information->arguments_array = tokenizeString(information->argument, " \t");

		/* If the argument vector is not successfully created, */
		/* allocate and set it manually. */
		if (!information->arguments_array)
		{
			information->arguments_array = malloc(sizeof(char *) * 2);
			if (information->arguments_array)
			{
				information->arguments_array[0] = str_duplicate(information->argument);
				information->arguments_array[1] = NULL;
			}
		}

		/* Count the number of arguments in the vector. */
		for (argumentCount = 0; information->arguments_array &&
								information->arguments_array[argumentCount];
			 argumentCount++)
			;

		/* Set the argument count in the structure. */
		information->argument_count = argumentCount;

		/* Step 3: Replace aliases in the argument vector. */
		alias_replacer(information);

		/* Step 4: Replace variables in the argument vector. */
		variables_replacer(information);
	}
}

/**
 * information_clear - function clears the command information structure.
 *
 * This function sets various fields in the command information structure
 * to NULL or 0,
 * effectively clearing any information related to the current command.
 *
 * @information: Pointer to the command information structure.
 */
void information_clear(CommandInfo *information)
{
	/* Step 1: Clear the command argument. */
	information->argument = NULL;

	/* Step 2: Clear the argument vector and related information. */
	information->arguments_array = NULL;
	information->executable_path = NULL;
	information->argument_count = 0;
}

/**
 * information_free - function frees memory allocated
 * for the command information structure.
 *
 * This function deallocates memory associated
 * with the command information structure,
 * including the argument vector, environment variables, history,
 * aliases, and other allocated resources.
 * Optionally, it can free all resources, including the command
 * buffer and environment variables.
 *
 * @information: Pointer to the command information structure.
 * @all:  Flag indicating whether to free all resources (1)
 * or just the necessary ones (0).
 */
void information_free(CommandInfo *information, int all)
{
	/* Step 1: Free the argument vector. */
	freeStringArray(information->arguments_array);
	information->arguments_array = NULL;
	information->executable_path = NULL;

	/* Step 2: Free additional resources if the 'all' flag is set. */
	if (all)
	{
		/* Free the command buffer if not set. */
		if (!information->command_buffer)
			free(information->argument);

		/* Free the environment variable list. */
		if (information->environment_list)
			freeLinkedList(&(information->environment_list));

		/* Free the history list. */
		if (information->command_history)
			freeLinkedList(&(information->command_history));

		/* Free the alias list. */
		if (information->command_alias)
			freeLinkedList(&(information->command_alias));

		/* Free the environment variables array. */
		freeStringArray(information->environment_variables);
		information->environment_variables = NULL;

		/* Free the command buffer list. */
		freeAndSetNull((void **)information->command_buffer);

		/* Close the read file descriptor if it is greater than 2. */
		if (information->file_descriptor > 2)
			close(information->file_descriptor);

		/* Flush the output buffer. */
		print_char(BUFFER_F);
	}
}
