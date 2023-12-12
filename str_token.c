#include "shell.h"
/**
* tokenizeString - function tokenizes a string into words
* using a specified delimiter.
*
* This function tokenizes the input string 'str_in' into words using the
* specified delimiter 'delimiter'. It returns an array of strings, where each
* string corresponds to a word in the original string. The last element of the
* array is set to NULL. If memory allocation fails, it returns NULL.
*
* @str_in: The string to be tokenized.
* @delimiter: The delimiter used for tokenization. If NULL, the default is " ".
*
* Return: Returns an array of strings representing the words in 'str_in'.
* Returns NULL if 'str_in' is NULL, empty, or if memory allocation fails.
*/
char **tokenizeString(char *str_in, char *delimiter)
{
	int w, x, y, z, n = 0;

	char **tokenArray;

	if (str_in == NULL || str_in[0] == '\0')
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (w = 0; str_in[w] != '\0'; w++)
		if (!IfInDelimiterSet(str_in[w], delimiter) &&
			(IfInDelimiterSet(str_in[w + 1], delimiter) || !str_in[w + 1]))
		{
			n++;
		}
	if (n == 0)
		return (NULL);
	tokenArray = malloc((1 + n) * sizeof(char *));
	if (!tokenArray)
		return (NULL);
	for (w = 0, x = 0; x < n; x++)
	{
		while (IfInDelimiterSet(str_in[w], delimiter))
			w++;
		y = 0;
		while (!IfInDelimiterSet(str_in[w + y], delimiter) && str_in[w + y])
			y++;
		tokenArray[x] = malloc((y + 1) * sizeof(char));
		if (!tokenArray[x])
		{
			for (y = 0; y < x; y++)
				free(tokenArray[y]);
			free(tokenArray);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			tokenArray[x][z] = str_in[w++];
		tokenArray[x][z] = '\0';
	}
	tokenArray[x] = NULL;
	return (tokenArray);
}

#include <stdlib.h>

/**
* tokenizeString_D - finction tokenizes a string into words
* using a specified delimiter character.
*
* This function tokenizes the input string 'str_in' into words using the
* specified delimiter character 'delimiter'. It returns an array of strings,
* where each string corresponds to a word in the original string. The last
* element of the array is set to NULL. If memory allocation fails, it returns
* NULL.
*
* @str_in: The string to be tokenized.
* @delimiter: The delimiter character used for tokenization.
*
* Return: Returns an array of strings representing the words in 'str_in'.
* Returns NULL if 'str_in' is NULL, empty, or if memory allocation fails.
*/
char **tokenizeString_D(char *str_in, char delimiter)
{
	int w, x, y, z, n = 0;

	char **tokenArray;

	if (str_in == NULL || str_in[0] == '\0')
		return (NULL);
	for (w = 0; str_in[w] != '\0'; w++)
		if ((str_in[w] != delimiter && str_in[w + 1] == delimiter) ||
			(str_in[w] != delimiter && !str_in[w + 1]) || str_in[w + 1] == delimiter)
			n++;
	if (n == 0)
		return (NULL);
	tokenArray = malloc((1 + n) * sizeof(char *));
	if (!tokenArray)
		return (NULL);
	for (w = 0, x = 0; x < n; x++)
	{
		while (str_in[w] == delimiter && str_in[w] != delimiter)
			w++;
		y = 0;
		while (str_in[w + y] != delimiter && str_in[w + y] &&
				str_in[w + y] != delimiter)
			y++;
		tokenArray[x] = malloc((y + 1) * sizeof(char));
		if (!tokenArray[x])
		{
			for (y = 0; y < x; y++)
				free(tokenArray[y]);
			free(tokenArray);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			tokenArray[x][z] = str_in[w++];
		tokenArray[x][z] = '\0';
	}
	tokenArray[x] = NULL;
	return (tokenArray);
}
