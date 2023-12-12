#include "shell.h"

/**
* history_getFile - function get the full path to the history file.
*
* This function constructs the full path to the history
* file based on the user's home directory.
*
* @information: Pointer to the command information structure.
* Return: A dynamically allocated string containing the full path
*			to the history file, or NULL on memory allocation failure
*			or if the home directory is not set.
*/
char *history_getFile(CommandInfo *information)
{
	char *full_path;
	/* Step 1: Retrieve the user's home directory. */
	char *home_directory = getEnvironmentVariable(information, "HOME=");

	if (!home_directory)
		return (NULL);

	/* Step 2: Allocate memory for the full path. */
	full_path = malloc(sizeof(char) *
											(str_length(home_directory) + str_length(HISTORY_FILE) + 2));

	if (!full_path)
		return (NULL);

	/* Step 3: Construct the full path to the history file. */
	full_path[0] = '\0';
	str_copy(full_path, home_directory);
	str_concatenate(full_path, "/");
	str_concatenate(full_path, HISTORY_FILE);

	/* Step 4: Return the dynamically allocated string. */
	return (full_path);
}


/**
* history_writing - function write command history to a file.
*
* This function writes the command history stored
* in the information structure to a file.
*
* @information: Pointer to the command information structure.
*
* Return: 1 on success, -1 on failure.
*/
int history_writing(CommandInfo *information)
{
	ssize_t file_descriptor;
	char *file_name = history_getFile(information);

	StringList *node = NULL;

	/* Step 1: Check if the history file name is valid. */
	if (!file_name)
		return (-1);

	/* Step 2: Open the history file for writing. */
	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);

	/* Step 3: Check if the file was opened successfully. */
	if (file_descriptor == -1)
		return (-1);

	/* Step 4: Write each history entry to the file. */
	for (node = information->command_history; node; node = node->next)
	{
		print_str_fd(node->string, file_descriptor);
		print_char_fd('\n', file_descriptor);
	}

	/* Step 5: Flush the write buffer and close the file. */
	print_char_fd(BUFFER_F, file_descriptor);
	close(file_descriptor);

	/* Step 6: Return success. */
	return (1);
}

/**
* print_command_history - function print the command history.
*
* This function prints the command history
* from the command information structure.
*
* @information: Pointer to the command information structure.
* Return: Always returns 0.
*/
int print_command_history(CommandInfo *information)
{
	printLinkedList(information->command_history);
	return (0);
}

