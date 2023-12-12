#include "shell.h"
/**
* print_char - function outputs a character
* to the standard output with buffering.
*
* This function buffers characters in an internal buffer
* and flushes the buffer to the standard output stream when it is full
* or when a specific flushing character (BUFFER_F) is encountered.
* It returns 1 on successful execution.
*
* @character: The character to be output to the standard output stream.
*
* Return: Returns 1 on successful execution.
*/

int print_char(char character)
{
	static int bufferIndex;

	static char buffer[BUFFER_WR];

	/*Check if the character is the flushing character or the buffer is full */
	if (character == BUFFER_F || bufferIndex >= BUFFER_WR)
	{
		/*Flush the buffer to the standard output stream */
		write(1, buffer, bufferIndex);
		bufferIndex = 0;
	}

	/*If the character is not the flushing character, store it in the buffer */
	if (character != BUFFER_F)
		buffer[bufferIndex++] = character;

	/*Return 1 on successful execution */
	return (1);
}

/**
* print_str - function outputs a string to the standard output.
*
* This function prints the characters of the provided string to the standard
* output. If the input string is NULL, the function returns without printing
* anything.
*
* @inputString: The string to be printed to the standard output.
*
*/
void print_str(char *inputString)
{
	int index = 0;

	/* Step 1: Check if the input string is NULL */
	if (!inputString)
		return;

	/* Step 2: Iterate through each character in the string */
	while (inputString[index] != '\0')
	{
		/* Step 3: Output each character using the _putchar function */
		print_char(inputString[index]);
		index++;
	}
}

/**
* print_int_fd - function prints an integer to the specified file descriptor.
*
* This function prints an integer to the specified file descriptor using the
* provided character output function (_putchar or _eputchar). It returns the
* count of characters printed.
*
* @integerValue: The integer value to be printed.
* @fileDescriptor: The file descriptor to which the integer is printed.
*
* Return: Returns the count of characters printed.
*/
int print_int_fd(int integerValue, int fileDescriptor)
{
	int (*outputCharFunction)(char) = print_char;
	int i, characterCount = 0;

	unsigned int absoluteValue, currentDigit;

	/* Step 1: Set the output character function based on the file descriptor */
	if (fileDescriptor == STDERR_FILENO)
		outputCharFunction = error_print_char;

	/* Determine the absolute value and print '-' if the integer is negative */
	if (integerValue < 0)
	{
		absoluteValue = -integerValue;
		outputCharFunction('-');
		characterCount++;
	}
	else
	{
		absoluteValue = integerValue;
	}

	currentDigit = absoluteValue;

	/* Step 3: Iterate through each digit of the integer and print it */
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoluteValue / i)
		{
			outputCharFunction('0' + currentDigit / i);
			characterCount++;
		}
		currentDigit %= i;
	}

	/* Step 4: Print the last digit of the integer */
	outputCharFunction('0' + currentDigit);
	characterCount++;

	/* Step 5: Return the count of characters printed */
	return (characterCount);
}

/**
* print_char_fd - function outputs a character to
* the specified file descriptor with buffering.
*
* This function buffers characters in an internal buffer and flushes the buffer
* to the specified file descriptor when it is full or when a specific flushing
* character (BUFFER_F) is encountered. It returns 1 on successful execution.
*
* @character: The character to be output to the specified file descriptor.
* @fileDescriptor:1 The file descriptor to which the character is output.
*
* Return: Returns 1 on successful execution.
*/
int print_char_fd(char character, int fileDescriptor)
{
	static int bufferIndex;

	static char buffer[BUFFER_WR];

	/*Check if the character is the flushing character or the buffer is full */
	if (character == BUFFER_F || bufferIndex >= BUFFER_WR)
	{
		/* Step 2: Flush the buffer to the specified file descriptor */
		write(fileDescriptor, buffer, bufferIndex);
		bufferIndex = 0;
	}

	/*If the character is not the flushing character, store it in the buffer */
	if (character != BUFFER_F)
		buffer[bufferIndex++] = character;

	/* Step 4: Return 1 on successful execution */
	return (1);
}

/**
* print_str_fd - function outputs a string
* to the specified file descriptor with buffering.
*
* This function prints the characters of the provided string to the specified
* file descriptor using the `print_char_fd` function for character output.
* If the input string is NULL, the function returns 0.
* Otherwise, it returns the count of characters printed.
*
* @inputString: The string to be printed to the specified file descriptor.
* @fileDescriptor: The file descriptor to which the string is printed.
*
* Return: Returns the count of characters printed
* or 0 if the input string is NULL.
*/
int print_str_fd(char *inputString, int fileDescriptor)
{
	int characterCount = 0;

	/* Step 1: Check if the input string is NULL */
	if (!inputString)
		return (0);

	/*Iterate through each character in the string and use _putfd for output */
	while (*inputString)
	{
		characterCount += print_char_fd(*inputString++, fileDescriptor);
	}

	/* Step 3: Return the count of characters printed */
	return (characterCount);
}

