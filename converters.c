#include "shell.h"


/**
* convert_str_int - function converts a string to an integer.
*
* This function parses a string and converts it to an integer. It considers
* integer values and takes into account the sign of the number. The function
* stops parsing when it encounters a non-digit character
* after parsing at least one digit.
*
* @str: The input string to be converted to an integer.
*
* Return: Returns the converted integer value.
*/
int convert_str_int(char *str)
{
	int index, sign = 1, digitFlag = 0, resultInteger;

	unsigned int result = 0;

	/* Step 1: Iterate through each character in the string */
	for (index = 0; str[index] != '\0' && digitFlag != 2; index++)
	{
		/* Step 2: Check if the current character is a minus sign */
		if (str[index] == '-')
			sign *= -1;

		/* Step 3: Check if the current character is a digit */
		if (str[index] >= '0' && str[index] <= '9')
		{
			/*Set digitFlag to 1 indicating the presence of at least one digit */
			digitFlag = 1;
			/*Update the result by multiplying it by 10 and adding the digit value */
			result *= 10;
			result += (str[index] - '0');
		}
		/*If a digit has already been encountered,*/
		/* set digitFlag to 2 to stop parsing */
		else if (digitFlag == 1)
			digitFlag = 2;
	}

	/* Step 7: Determine the final resultInteger by considering the sign */
	if (sign == -1)
		resultInteger = -result;
	else
		resultInteger = result;

	/* Step 8: Return the converted integer value */
	return (resultInteger);
}

/**
* conver_longInt_str - function converts a long integer
* to a string representation in a specified base.
* This function converts the long integer 'number' to
* a string representation in the specified 'base'.
* The 'flags' parameter can be used to specify additional
* options like CON_UNS and CON_LOWER. The result is stored in a
* static buffer, and a pointer to the result is returned.
*
* @number: The long integer to be converted.
* @base: The base for the conversion (e.g., 10 for decimal,16 for hexadecimal).
* @flags: Additional conversion options (e.g., CON_UNS, CON_LOWER).
*
* Return: Returns a pointer to the converted string.
*/
char *conver_longInt_str(long int number, int base, int flags)
{
	static char *digitArray;

	static char resultBuffer[50];

	char sign = 0;

	char *resultPtr;

	unsigned long x = (unsigned long)number;

	/* Step 1: Handle the sign for non-unsigned conversions */
	if (!(flags & CON_UNS) && number < 0)
	{
		x = -number;
		sign = '-';
	}

	/* Step 2: Choose the digit array based on whether lowercase is specified */
	digitArray = flags & CON_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";

	/* Step 3: Initialize the result pointer to the end of the buffer */
	resultPtr = &resultBuffer[49];
	*resultPtr = '\0';

	/* Step 4: Perform the conversion */
	do {
		*--resultPtr = digitArray[x % base];
		x /= base;
	} while (x != 0);

	/* Step 5: Add the sign to the result if necessary */
	if (sign)
		*--resultPtr = sign;

	/* Step 6: Return a pointer to the converted string */
	return (resultPtr);
}

/**
* convert_list_arrstr - function converts a linked list of
* strings into an array of strings.
*
* This function converts a linked list of strings into an array of strings.
* It allocates memory for the array and each individual string, copying the
* content of each string in the linked list to the corresponding element in
* the array. The resulting array is terminated with a NULL pointer.
*
* @head: A pointer to the head of the linked list.
*
* Return: Returns a dynamically allocated array of strings or NULL on failure.
*/
char **convert_list_arrstr(StringList *head)
{
	StringList *my_node = head;
	size_t listLength = getLinkedListLength(head), i, j;
	char **stringArray;

	char *string;

	/* Step 1: Check if the linked list is empty or NULL */
	if (!head || !listLength)
		return (NULL);

	/* Step 2: Allocate memory for the array of strings */
	stringArray = malloc(sizeof(char *) * (listLength + 1));
	if (!stringArray)
		return (NULL);

	/* Step 3:Iterate through the linked list and copy each string to the array */
	for (i = 0; my_node; my_node = my_node->next, i++)
	{
		/* Step 4: Allocate memory for the individual string */
		string = malloc(str_length(my_node->string) + 1);
		if (!string)
		{
			/* Step 5: Free memory in case of failure and return NULL */
			for (j = 0; j < i; j++)
				free(stringArray[j]);
			free(stringArray);
			return (NULL);
		}

		/* Step 6: Copy the content of the string in the linked list to the array */
		string = str_copy(string, my_node->string);
		stringArray[i] = string;
	}

	/* Step 7: Terminate the array with a NULL pointer */
	stringArray[i] = NULL;

	/* Step 8: Return the dynamically allocated array of strings */
	return (stringArray);
}

/**
* variables_replacer - function replaces variables in command arguments.
*
* This function replaces variables like "$?", "$$", and environment variables
* in the command arguments with their corresponding values.
*
* @information:Apointer to the info_t structure containing command information.
*
* Return: 0 on success, 1 on failure.
*/
int variables_replacer(CommandInfo *information)
{
	int i = 0;

	StringList *my_node;

	for (i = 0; information->arguments_array[i]; i++)
	{
		if (information->arguments_array[i][0] != '$' ||
														!information->arguments_array[i][1])
			continue;

		if (!str_compare(information->arguments_array[i], "$?"))
		{
			str_replacer(&(information->arguments_array[i]),
					str_duplicate(conver_longInt_str(information->execution_status, 10, 0)));
			continue;
		}
		if (!str_compare(information->arguments_array[i], "$$"))
		{
			str_replacer(&(information->arguments_array[i]),
						  str_duplicate(conver_longInt_str(getpid(), 10, 0)));
			continue;
		}
		my_node = findNodeWithPrefix(information->environment_list,
																&information->arguments_array[i][1], '=');
		if (my_node)
		{
			str_replacer(&(information->arguments_array[i]),
						  str_duplicate(char_in_str(my_node->string, '=') + 1));
			continue;
		}
		str_replacer(&information->arguments_array[i], str_duplicate(""));
	}
	return (0);
}
