#include "shell.h"
#include <fcntl.h>
#include <linux/stat.h>
#include <sys/stat.h>
/**
* isAlphabeticCharacter - function checks if a given character
* is an alphabetic character.
*
* This function evaluates whether the provided character
* falls within the range of lowercase ('a' to 'z')
*		or					uppercase ('A' to 'Z') alphabetic characters.
*
* @character: The character to be checked for alphabetic status.
*
* Return: Returns 1 if the character is alphabetic, otherwise returns 0.
*/
int isAlphabeticCharacter(int character)
{
	/*Check if the character is within the range of lowercase alphabets */
	if ((character >= 'a' && character <= 'z') ||
	/*Check if the character is within the range of uppercase alphabets */
		(character >= 'A' && character <= 'Z'))
	{
		/* Step 3: Return 1 if the character is an alphabetic character */
		return (1);
	}
	else
	{
		/* Step 4: Return 0 if the character is not an alphabetic character */
		return (0);
	}
}

/**
* IfInDelimiterSet - function checks if a character is a delimiter
* by comparing it with a set of delimiters.
*
* This function iterates through each character in the
* provided delimiter stringand checks if any of them match the given character.
* If a match is found, the function returns 1,
* indicating that the character is a delimiter; otherwise, it returns 0.
*
* @targetChar: The character to be checked for being a delimiter.
* @delimiterSet: Pointer to a null-terminated string containing
* delimiter characters.
*
* Return: Returns 1 if the character is a delimiter, otherwise returns 0.
*/

int IfInDelimiterSet(char targetChar, char *delimiterSet)
{
	/* Iterate through each character in the delimiter string */
	while (*delimiterSet)
	{
		/* Check if the current character */
		/* in the delimiter string matches the given character */
		if (*delimiterSet++ == targetChar)
		{
			/* Return 1 if a match is found (character is a delimiter) */
			return (1);
		}
	}

	/* Return 0 if no match is found (character is not a delimiter) */
	return (0);
}

/**
* isInteractiveShell - function checks if the current shell is interactive.
*
* This function examines whether the standard input
* is associated with a terminal and if the 'file_descriptor'
* member of the provided CommandInfo structure
* is within the standard input range.
* The result is a logical AND combination of these checks,
* indicating whether the shell is interactive.
*
* @information: Pointer to a CommandInfo structure containing file descriptor
* information.
*
* Return: Returns 1 if the shell is interactive (both conditions are true),
*         otherwise returns 0.
*/

int isInteractiveShell(CommandInfo *information)
{
	/* Step 1: Check if the standard input is associated with a terminal */

	/* Step 2: Check if the 'file_descriptor' member */
	/* is within the standard input range */

	/* Return 1 if both conditions are true (shell is interactive),*/
	/* otherwise return 0 */
	return ((isatty(STDIN_FILENO) && information->file_descriptor <= 2));
}

/**
* isCommand - function checks if the given path
* corresponds to an executable command.
*
* This function checks if the specified path corresponds to an executable
* command. It uses the stat function to determine if the path exists and
* corresponds to a regular file (indicating an executable).
*
* @information: A pointer to the structure containing command arguments and
* environment information. (Not used in this function)
* @path: The path of the file to be checked.
*
* Return: Returns 1 if the path corresponds to an executable command,
* otherwise returns 0.
*/
int isCommand(CommandInfo *information, char *path)
{
	struct stat fileStat;

	(void)information;
	/* Step 1: Check if the path is valid or if stat fails */
	if (!path || stat(path, &fileStat))
		return (0);

	/* Step 2: Check if the path corresponds to a regular file (executable) */
	if (fileStat.st_mode & 0100000)
	{
		return (1); /* The path corresponds to an executable command */
	}

	/* Step 3:Return 0 if the path does not correspond to an executable command */
	return (0);
}
