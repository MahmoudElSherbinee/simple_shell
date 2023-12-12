#include "shell.h"

/**
 * Comment_Remover - function removes comments from a string.
 *
 * This function iterates through the characters in the input string and
 * removes comments that start with '#' and are either at the beginning of
 * the string or preceded by a space. It modifies the input string in place.
 *
 * @buffer: A pointer to the input string containing comments.
 */
void Comment_Remover(char *buffer)
{
	int x;

	/* Iterate through the characters in the input string. */
	for (x = 0; buffer[x] != '\0'; x++)
	{
		/* Check if the character is '#' and is */
		/* either at the beginning or preceded by a space. */

		if (buffer[x] == '#' && (!x || buffer[x - 1] == ' '))
		{
			/* Replace the '#' and the following characters */
			/* with '\0' to remove the comment. */
			buffer[x] = '\0';
			/* Break out of the loop after removing the comment. */
			break;
		}
	}
}
