#include "shell.h"

/**
* duplicate_characters - function duplicate characters
* from a string within a specified range.
* This function duplicates characters from a given string within the specified
* range [first, end), excluding the character ':'.
* The result is stored in a static buffer and the pointer to it is returned.
* Note: The returned buffer may be overwritten
* with subsequent calls to this function.
*
* @path_str: The input string from which characters are duplicated.
* @first: The starting index of the range (inclusive).
* @end: The stopping index of the range (exclusive).
*
* Return: Pointer to the duplicated characters (static buffer).
*/
char *duplicate_characters(const char *path_str, int first, int end)
{
	static char buffer[1024];

	int x = 0, y = 0;

	for (y = 0, x = first; x < end; x++)
	{
		if (path_str[x] != ':')
		{
			buffer[y++] = path_str[x];
		}
	}

	buffer[y] = 0;
	return (buffer);
}

/**
 * find_command_path - function find the full my_path of a
 * command in the given PATH string.
 *
 * This function searches for the full my_path of a
 * command in the specified PATH string.
 * If the command is found in any of the directories in the PATH,
 * the full my_path is returned.
 * If the command includes "./" and is a valid command,
 * the command itself is returned.
 *
 * @information: Pointer to the information structure.
 * @path_str: The PATH string containing directories separated by ':'.
 * @command: The command to find in the PATH.
 *
 * Return: Pointer to the full my_path of the command if found, NULL otherwise.
 */
char *find_command_path(CommandInfo *information,
												char *path_str, char *command)
{
	int x = 0, current_position = 0;
	char *my_path;

	if (!path_str)
		return (NULL);

	if ((str_length(command) > 2) && checkIfPrefix(command, "./"))
	{
		if (isCommand(information, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[x] || path_str[x] == ':')
		{
			my_path = duplicate_characters(path_str, current_position, x);
			if (!*my_path)
				str_concatenate(my_path, command);
			else
			{
				str_concatenate(my_path, "/");
				str_concatenate(my_path, command);
			}

			if (isCommand(information, my_path))
				return (my_path);

			if (!path_str[x])
				break;

			current_position = x;
		}
		x++;
	}
	return (NULL);
}
