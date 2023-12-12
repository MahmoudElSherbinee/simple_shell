#include "shell.h"

/**
 * detectCommandChain - function determines if
 * the current position in the buffer indicates a command chain.
 *
 * This function checks if the current position in the buffer indicates a
 * command chain (logical AND, logical OR, or command termination). If a chain
 * is found, it updates the buffer and
 * the command buffer type in the information structure.
 *
 * @information: A pointer to the structure containing command arguments and
 * environment information.
 * @buffer: A pointer to the buffer containing user input.
 * @position: A pointer to the current position in the buffer.
 *
 * Return: Returns 1 if a command chain is found, 0 otherwise.
 */
int detectCommandChain(CommandInfo *information,
					   char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		information->command_buffer_type = COMMAND_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		information->command_buffer_type = COMMAND_AND;
	}
	else if (buffer[index] == ';')
	{
		buffer[index] = 0;
		information->command_buffer_type = COMMAND_CHAIN;
	}
	else
	{
		return (0);
	}

	*position = index;
	return (1);
}

/**
 * handleCommandChain - function checks and handles command chaining
 * based on the current command buffer type.
 *
 * This function checks the command buffer type in the information structure
 * and updates the buffer accordingly for logical AND and logical OR cases.
 *
 * @information: A pointer to the structure containing command arguments and
 * environment information.
 * @buffer: A pointer to the buffer containing user input.
 * @position: A pointer to the current position in the buffer.
 * @currentIndex: The current index in the buffer.
 * @bufferLength: The length of the buffer.
 */
void handleCommandChain(CommandInfo *information, char *buffer,
						size_t *position, size_t currentIndex, size_t bufferLength)
{
	size_t index = *position;

	if (information->command_buffer_type == COMMAND_AND)
	{
		if (information->execution_status)
		{
			buffer[currentIndex] = 0;
			index = bufferLength;
		}
	}

	if (information->command_buffer_type == COMMAND_OR)
	{
		if (!information->execution_status)
		{
			buffer[currentIndex] = 0;
			index = bufferLength;
		}
	}

	*position = index;
}
