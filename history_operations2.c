#include "shell.h"

/**
* history_buildList - function build the command history list.
*
* This function adds a new history entry to
* the command history list in the info structure.
*
* @information: Pointer to the command information structure.
* @buffer: Command string to be added to the history list.
* @line_count: Line count associated with the command.
*
* Return: 0 on success, 1 on failure.
*/
int history_buildList(CommandInfo *information, char *buffer, int line_count)
{
	StringList *node = NULL;

	/* Step 1: Check if the history list is non-empty. */
	if (information->command_history)
		node = information->command_history;

	/* Step 2: Add a new node to the end of the history list. */
	addNodeToEndOfList(&node, buffer, line_count);

	/* Step 3: Update the history list in the command information structure. */
	if (!information->command_history)
		information->command_history = node;

	/* Step 4: Return success. */
	return (0);
}

/**
* history_reNumber - function renumber the command history list.
*
* This function renumbers the command history list in the info structure.
*
* @information: Pointer to the command information structure.
*
* Return: The updated history count.
*/
int history_reNumber(CommandInfo *information)
{
	StringList *node = information->command_history;
	int count = 0;

	/* Iterate through the history list, reassigning numbers. */
	while (node)
	{
		node->number = count++;
		node = node->next;
	}

	/* Update the history count in the command information structure. */
	information->history_count = count;

	/* Return the updated history count. */
	return (count);
}

/**
* history_reading - function read command history from a file.
*
* This function reads command history from a file
* and populates the history list in the info structure.
*
* @information: Pointer to the command information structure.
* Return: Number of history entries read, 0 on failure.
*/
int history_reading(CommandInfo *information)
{
	int i, last = 0, line_count = 0;

	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *file_name = history_getFile(information);

	if (!file_name)
		return (0);
	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);

	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (close(file_descriptor), 0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (close(file_descriptor), 0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), close(file_descriptor), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			history_buildList(information, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		history_buildList(information, buffer + last, line_count++);
	free(buffer);
	information->history_count = line_count;
	while (information->history_count-- >= HISTORY_MAX)
		deleteNodeAtIndexInList(&(information->command_history), 0);
	history_reNumber(information);
	return (information->history_count);
}
