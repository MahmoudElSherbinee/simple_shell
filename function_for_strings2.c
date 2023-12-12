#include "shell.h"

/**
* str_concatenate - function concatenates two strings.
*
* This function concatenates the string 'src' to the end of the string 'dest'.
* It returns a pointer to the resulting concatenated string, which is the same
* as the original 'dest' string.
*
* @destinationString: The destination string to which 'src' is appended.
* @sourceString: The source string to be appended to 'dest'.
*
* Return: Returns a pointer to the resulting concatenated string.
*/
char *str_concatenate(char *destinationString, char *sourceString)
{
	char *result = destinationString;

	/* Step 1: Move to the end of the destination string */
	while (*destinationString)
		destinationString++;

	/* Step 2: Copy the characters of the source string */
	/* to the end of the destination string */
	while (*sourceString)
		*destinationString++ = *sourceString++;

	/* Step 3: Append the null terminator to the resulting concatenated string */
	*destinationString = *sourceString;

	/* Step 4: Return a pointer to the resulting concatenated string */
	return (result);
}

/**
* str_n_concatenate - function concatenates
* at most the first n characters of two strings.
*
* This function concatenates, at most, the first 'n' characters of the string
* 'src' to the end of the string 'dest'. It returns a pointer to the resulting
* concatenated string, which is the same as the original 'dest' string.
*
* @destinationString: The destination string to which 'src' is appended.
* @sourceString: The source string to be appended to 'dest'.
* @max: The maximum number of characters to append from 'src'.
*
* Return: Returns a pointer to the resulting concatenated string.
*/
char *str_n_concatenate(char *destinationString, char *sourceString, int max)
{
	char *result = destinationString;

	int index = 0, x = 0;

	/* Step 1: Move to the end of the destination string */
	while (destinationString[index] != '\0')
		index++;

	/* Step 2: Copy the first 'n' characters of the source string */
	/* to the end of the destination string */
	while (sourceString[x] != '\0' && x < max)
	{
		destinationString[index] = sourceString[x];
		index++;
		x++;
	}

	/* Step 3: Append the null terminator to the */
	/* resulting concatenated string if 'x' is less than 'n' */
	if (x < max)
		destinationString[index] = '\0';

	/* Step 4: Return a pointer to the resulting concatenated string */
	return (result);
}

/**
* str_copy - function copies a string to a destination string.
*
* This function copies the string 'src' to the destination string 'dest'. It
* returns a pointer to the resulting copied string.
*
* @destinationString: The destination string to which 'src' is copied.
* @sourceString: The source string to be copied to 'dest'.
*
* Return: Returns a pointer to the resulting copied string.
*/
char *str_copy(char *destinationString, char *sourceString)
{
	int index = 0;

	/*Check for cases where 'dest' and 'src' are the same or 'src' is NULL */
	if (destinationString == sourceString || sourceString == 0)
		return (destinationString);

	/* Step 2: Copy the characters of 'src' to 'dest' */
	while (sourceString[index])
	{
		destinationString[index] = sourceString[index];
		index++;
	}

	/* Step 3: Append the null terminator to the resulting copied string */
	destinationString[index] = 0;

	/* Step 4: Return a pointer to the resulting copied string */
	return (destinationString);
}

/**
* str_n_copy - function copies at
* most the first n characters of a string to another string.
*
* This function copies, at most, the first 'n' characters of the string 'src'
* to the string 'dest'. It returns a pointer to the resulting copied string,
* which is the same as the original 'dest' string.
*
* @destinationString: The destination string to which 'src' is copied.
* @sourceString: The source string to be copied to 'dest'.
* @max: The maximum number of characters to copy from 'src'.
*
* Return: Returns a pointer to the resulting copied string.
*/
char *str_n_copy(char *destinationString, char *sourceString, int max)
{
	int index = 0, x;

	/* Step 1: Copy at most the first 'n' characters of 'src' to 'dest' */
	while (sourceString[index] != '\0' && index < max - 1)
	{
		destinationString[index] = sourceString[index];
		index++;
	}

	/* Step 2: Append null characters to 'dest' if 'index' is less than 'n' */
	if (index < max)
	{
		x = index;
		while (x < max)
		{
			destinationString[x] = '\0';
			x++;
		}
	}

	/* Step 3: Return a pointer to the resulting copied string */
	return (destinationString);
}

/**
* str_duplicate - function duplicates a string.
*
* This function duplicates the input string 'originalString' by allocating
* memory for a new string and copying the characters. It returns a pointer
* to the duplicated string.
*
* @originalString: The string to be duplicated.
*
* Return: Returns a pointer to the duplicated string.
*Returns NULL if 'originalString' is NULL or if memory allocation fails.
*/
char *str_duplicate(const char *originalString)
{
	int length = 0;

	char *duplicate;

	/* Step 1: Check if the input string is NULL */
	if (originalString == NULL)
		return (NULL);

	/* Step 2: Calculate the length of the input string */
	while (*originalString++)
		length++;

	/* Step 3: Allocate memory for the duplicated string */
	duplicate = malloc(sizeof(char) * (length + 1));

	/* Step 4: Check if memory allocation was successful */
	if (!duplicate)
		return (NULL);

	/*Copy the characters from the input string to the duplicated string */
	for (length++; length--;)
		duplicate[length] = *--originalString;

	/* Step 6: Return a pointer to the duplicated string */
	return (duplicate);
}
