#include "shell.h"

/**
* str_length - function calculates the length of a string.
*
* This function iterates through the characters of the provided string
* and counts the number of characters until the null terminator is encountered.
* If the input string is NULL, the function returns 0.
*
* @inputString: The string for which the length is calculated.
*
* Return: Returns the length of the string or 0 if the input string is NULL.
*/
int str_length(char *inputString)
{
	int length = 0;

	/* Step 1: Check if the input string is NULL */
	if (!inputString)
		return (0);

	/* Step 2: Iterate through the characters of the string */
	/* until the null terminator is encountered */
	while (*inputString++)
		length++;

	/* Step 3: Return the calculated length */
	return (length);
}

/**
* str_compare - function compares two strings lexicographically.
*
* This function compares the characters of two strings lexicographically.
* It returns an integer less than, equal to, or greater than zero if the first
* string is found to be less than, equal to, or greater than the second string,
* respectively. If both strings are equal, the function returns 0.
*
* @str1: The first string to be compared.
* @str2: The second string to be compared.
*
* Return: Returns an integer less than, equal to, or greater than zero based on
* the lexicographical comparison of the two strings.
*/
int str_compare(char *str1, char *str2)
{
	/* Step 1: Iterate through the characters of both strings */
	/* until a null terminator is encountered */
	while (*str1 && *str2)
	{
		/* Step 2: Compare the current characters of both strings */
		if (*str1 != *str2)
			return (*str1 - *str2);

		/* Step 3: Move to the next characters in both strings */
		str1++;
		str2++;
	}

	/* Step 4: Check if both strings are equal */
	/* or if one of them has reached the null terminator */
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
* char_in_str - function locates the first occurrence
* of a character in a string.
*
* This function searches for the first occurrence of the specified character
* 'c' in the string 's'. If the character is found, a pointer to the first
* occurrence is returned; otherwise, NULL is returned.
*
* @searchString: The string to be searched.
* @targetChar: The character to be located in the string.
*
* Return: Returns a pointer to the first occurrence of
* 'targetChar' in 'searchString',
* or NULL if 'targetChar' is not found in 'searchString'.
*/
char *char_in_str(char *searchString, char targetChar)
{
	/* Step 1: Iterate through the characters of the string */
	/* until a null terminator is encountered */
	do {
		/*Check if the current character is equal to the target character */
		if (*searchString == targetChar)
			return (searchString);

	} while (*searchString++ != '\0');

	/* Step 3: Return NULL if the target character is not found in the string */
	return (NULL);
}

/**
* checkIfPrefix - function checks if a string is a prefix of another string.
*
* This function checks if the string 'needle'
* is a prefix of the string 'haystack'.
* If 'needle' is a prefix, it returns
* a pointer to the character in 'haystack' where
* 'needle' begins; otherwise, it returns NULL.
*
* @haystack: The string to be checked for the prefix.
* @needle: The prefix string to be checked.
*
* Return: Returns a pointer to the character in 'haystack'
* where 'needle' begins, or NULL if 'needle' is not a prefix of 'haystack'.
*/
char *checkIfPrefix(const char *haystack, const char *needle)
{
	/* Step 1: Iterate through the characters of 'needle' */
	while (*needle)
	{
		/* Step 2: Check if the current character in 'needle' is equal */
		/* to the corresponding character in 'haystack' */
		if (*needle++ != *haystack++)
			return (NULL);
	}

	/*Return a pointer to the character in 'haystack' where 'needle' begins */
	return ((char *)haystack);
}

/**
* str_replacer - function replaces an old string with a new one.
*
* This function frees the memory occupied by the old string and updates
* the pointer with the new string.
*
* @oldString: A pointer to the old string.
* @newString: The new string to replace the old one.
*
* Return: 1 on success, 0 on failure.
*/
int str_replacer(char **oldString, char *newString)
{
	free(*oldString);
	*oldString = newString;
	return (1);
}
