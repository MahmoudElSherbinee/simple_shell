#include "shell.h"

/**
 * error_str_to_int - function converts a string to an integer
 * with error handling.
 *
 * This function parses a string and converts it to an integer. It considers
 * integer values and takes into account the sign of the number. The function
 * performs error handling by checking for overflow and non-digit characters.
 * If an error is detected, the function returns -1; otherwise, it returns the
 * converted integer value.
 *
 * @str: The input string to be converted to an integer.
 *
 * Return: Returns the converted integer value if successful, or -1 on error.
 */
int error_str_to_int(char *str)
{
	int index;

	unsigned long int result = 0;

	/* Step 1: Skip leading '+' sign, if present */
	if (*str == '+')
		str++;

	/* Step 2: Iterate through each character in the string */
	for (index = 0; str[index] != '\0'; index++)
	{
		/* Step 3: Check if the current character is a digit */
		if (str[index] >= '0' && str[index] <= '9')
		{
			/*Update the result by multiplying it by 10 and adding the digit value */
			result *= 10;
			result += (str[index] - '0');

			/* Step 5: Check for overflow */
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			/* Step 6: Return -1 on encountering a non-digit character */
			return (-1);
		}
	}

	/* Step 7: Return the converted integer value */
	return (result);
}

/**
 * error_print_char - function outputs a character
 * to the standard error stream with buffering.
 *
 * This function buffers characters in an internal buffer
 * and flushes the buffer to the standard error stream when it is full
 * or when a specific flushing character (BUF_FLUSH) is encountered.
 * It returns 1 on successful execution.
 *
 * @character: The character to be output to the standard error stream.
 *
 * Return: Returns 1 on successful execution.
 */
int error_print_char(char character)
{
	static int bufferIndex;

	static char buffer[BUFFER_WR];

	/*Check if the character is the flushing character or the buffer is full */
	if (character == BUFFER_F || bufferIndex >= BUFFER_WR)
	{
		/*Flush the buffer to the standard error stream */
		write(2, buffer, bufferIndex);
		bufferIndex = 0;
	}

	/*If the character is not the flushing character, store it in the buffer */
	if (character != BUFFER_F)
		buffer[bufferIndex++] = character;

	/*Return 1 on successful execution */
	return (1);
}

/**
 * error_print_str - function outputs a string to the standard output
 * with error handling.
 *
 * This function prints the characters of the provided string to the standard
 * output. It performs error handling by checking if the input string is NULL.
 * If the string is NULL, the function returns without printing anything.
 *
 * @inputString: The string to be printed to the standard output.
 */
void error_print_str(char *inputString)
{
	int index = 0;

	/* Step 1: Check if the input string is NULL */
	if (!inputString)
		return;

	/* Step 2: Iterate through each character in the string */
	while (inputString[index] != '\0')
	{
		/* Step 3: Output each character using the error_print_char function */
		error_print_char(inputString[index]);
		index++;
	}
}

/**
 * printErrorMessage - function prints an error message
 * to the standard error stream.
 *
 * This function prints an error message containing information such as the
 * filename, line number, command name, and a specific error string to the
 * standard error stream.
 *
 * @fileInfo: Pointer to a structure containing file information.
 * @errorString: The specific error string to be printed.
 */
void printErrorMessage(CommandInfo *fileInfo, char *errorString)
{
	/*Output the filename to the standard error stream */
	error_print_str(fileInfo->file_name);

	/*Output a separator and the line number to the standard error stream */
	error_print_str(": ");
	print_int_fd(fileInfo->current_line, STDERR_FILENO);

	/*Output a separator and the command name to the standard error stream */
	error_print_str(": ");
	error_print_str(fileInfo->arguments_array[0]);

	/*Output a separator and the specific error string */
	/* to the standard error stream */
	error_print_str(": ");
	error_print_str(errorString);
}
