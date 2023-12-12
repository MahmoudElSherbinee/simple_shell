#include "shell.h"
/**
* custom_getline - function custom implementation of getline.
*
* This function reads a line from the input and stores it in the provided
* buffer, reallocating memory as needed.
*
* @information: A pointer to the CommandInfo structure
* containing command information.
* @buffer: A pointer to the buffer that will store the line.
* @buffer_size: A pointer to the size of the buffer.
*
* Return: The number of characters read on success, -1 on failure.
*/
ssize_t custom_getline(CommandInfo *information,
					   char **buffer, size_t *buffer_size)
{
	static char read_buffer[BUFFER_RD];

	static size_t buffer_index, read_buffer_size;
	size_t characters_read;
	ssize_t read_result = 0, temp = 0;
	char *current_buffer = NULL, *new_buffer = NULL, *newline_position;

	current_buffer = *buffer;
	if (current_buffer && buffer_size)
		temp = *buffer_size;
	if (buffer_index == read_buffer_size)
		buffer_index = read_buffer_size = 0;

	read_result = read_input_buffer(information, read_buffer, &read_buffer_size);
	if (read_result == -1 || (read_result == 0 && read_buffer_size == 0))
		return (-1);

	newline_position = char_in_str(read_buffer + buffer_index, '\n');
	characters_read = newline_position ?
									1 + (unsigned int)(newline_position - read_buffer) : read_buffer_size;
	new_buffer = realloc_Memory
			(current_buffer, temp, temp ? temp + characters_read : characters_read + 1);
	if (!new_buffer)
		return (current_buffer ? free(current_buffer), -1 : -1);

	if (temp)
		str_n_concatenate
						(new_buffer, read_buffer + buffer_index, characters_read - buffer_index);
	else
		str_n_copy
		(new_buffer, read_buffer + buffer_index, characters_read - buffer_index + 1);

	temp += characters_read - buffer_index;
	buffer_index = characters_read;
	current_buffer = new_buffer;

	if (buffer_size)
		*buffer_size = temp;
	*buffer = current_buffer;
	return (temp);
}

/**
* readUserInput - function reads input from the user
* and stores it in the buffer.
*
* This function reads input from the user and stores it in the buffer. If the
* buffer is empty, it fills the buffer with user input, removes trailing
* newline characters, and handles comments and history updates.
*
* @information: A pointer to the structure containing command arguments and
* environment information.
* @buffer: A pointer to the buffer for storing user input.
* @buffer_size: A pointer to the buffer_size of the buffer.
*
* Return: Returns the number of characters read on success, -1 on failure, and
* 0 if no characters were read (end of input).
*/
ssize_t readUserInput(CommandInfo *information,
												char **buffer, size_t *buffer_size)
{
	ssize_t bytesRead = 0;
	size_t bufferLength = 0;

	/* Step 1: Check if the buffer is empty */
	if (!*buffer_size)
	{
		/* Free the buffer if it'temp not empty */
		free(*buffer);
		*buffer = NULL;
		/* Set the SIGINT signal handler and read input */
		signal(SIGINT, handleSigInt);
#if GETLINE
		/* Use getline to read input from the user */
		bytesRead = getline(buffer, &bufferLength, stdin);
#else
		bytesRead = custom_getline(information, buffer, &bufferLength);
#endif
		/* Process the input if characters were read */
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			/* Update flags and history */
			information->linecount_indicator = 1;
			Comment_Remover(*buffer);
			history_buildList(information, *buffer, information->history_count++);
			*buffer_size = bytesRead;
			information->command_buffer = buffer;
		}
	}
	/* Step 2: Return the number of characters read */
	return (bytesRead);
}

/**
* read_input_buffer - function reads data from the input buffer.
*
* This function reads data from the input buffer and stores it in the provided
* buffer, updating the index accordingly.
*
* @information: A pointer to the CommandInfo structure
* containing command information.
* @buffer: A pointer to the buffer that will store the data.
* @index: A pointer to the index indicating the position in the buffer.
*
* Return: The number of bytes read on success, -1 on failure.
*/
ssize_t read_input_buffer(CommandInfo *information,
													char *buffer, size_t *index)
{
	ssize_t read_result = 0;

	if (*index)
		return (0);

	read_result = read(information->file_descriptor, buffer, BUFFER_RD);
	if (read_result >= 0)
		*index = read_result;

	return (read_result);
}

/**
* checkInput - function gets input from the command buffer.
*
* This function retrieves input from the command buffer,
* handling command chaining.
*
* @information: A pointer to the CommandInfo structure
* containing command information.
*
* Return: The buffer_size of the input on success, -1 on failure or EOF.
*/
ssize_t checkInput(CommandInfo *information)
{
	static char *command_chain_buffer;

	static size_t current_position, chain_start_position, buffer_length;
	ssize_t read_result = 0;
	char **buffer_pointer = &(information->argument), *current_char;

	print_char(BUFFER_F);
	read_result =
					readUserInput(information, &command_chain_buffer, &buffer_length);
	if (read_result == -1)
		return (-1);

	if (buffer_length)
	{
		chain_start_position = current_position;
		current_char = command_chain_buffer + current_position;

		handleCommandChain(information, command_chain_buffer,
															&chain_start_position, current_position, buffer_length);
		while (chain_start_position < buffer_length)
		{
			if (detectCommandChain(information,
												command_chain_buffer, &chain_start_position))
				break;
			chain_start_position++;
		}

		current_position = chain_start_position + 1;
		if (current_position >= buffer_length)
		{
			current_position = buffer_length = 0;
			information->command_buffer_type = COMMAND_NORMAL;
		}

		*buffer_pointer = current_char;
		return (str_length(current_char));
	}

	*buffer_pointer = command_chain_buffer;
	return (read_result);
}
