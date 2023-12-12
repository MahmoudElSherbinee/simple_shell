#include "shell.h"


/**
 * forkAndExecuteCommand - function forks and executes a command.
 *
 * Creates a child process using fork and executes the specified command
 * in the child process. The parent process waits for the child to complete.
 *
 * @information: Pointer to the information structure.
 */

void forkAndExecuteCommand(CommandInfo *information)
{
	pid_t childPid;

	childPid = fork();

	if (childPid == -1)
	{
		perror("Error:");
		return;
	}

	if (childPid == 0)
	{
		if (execve(information->executable_path, information->arguments_array,
				   getEnvironmentVariables(information)) == -1)
		{
			information_free(information, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(information->execution_status));

		if (WIFEXITED(information->execution_status))
		{
			information->execution_status = WEXITSTATUS(information->execution_status);

			if (information->execution_status == 126)
				printErrorMessage(information, "Permission denied\n");
		}
	}
}

/**
 * findAndExecuteCommand - function finds and executes the specified command.
 *
 * Searches for the command in the PATH environment variable and executes it.
 * If the command is not found, an error message is printed.
 *
 * @information: Pointer to the information structure.
 */
void findAndExecuteCommand(CommandInfo *information)
{
	char *commandPath = NULL;
	int x, wordCount;

	information->executable_path = information->arguments_array[0];

	if (information->linecount_indicator == 1)
	{
		information->current_line++;
		information->linecount_indicator = 0;
	}

	for (x = 0, wordCount = 0; information->argument[x]; x++)
		if (!IfInDelimiterSet(information->argument[x], " \t\n"))
			wordCount++;

	if (!wordCount)
		return;

	commandPath = find_command_path(information,
									getEnvironmentVariable(information, "PATH="),
									information->arguments_array[0]);

	if (commandPath)
	{	information->executable_path = commandPath;
		forkAndExecuteCommand(information);
	}
	else
	{
		if ((isInteractiveShell(information) ||
			 getEnvironmentVariable(information, "PATH=") ||
			 information->arguments_array[0][0] == '/') &&
			isCommand(information, information->arguments_array[0]))
		{
			forkAndExecuteCommand(information);
		}
		else if (*(information->argument) != '\n')
		{	information->execution_status = 127;
			printErrorMessage(information, "Command not found\n");
		}
	}
}

/**
 * customShell - function main function for the custom shell.
 *
 * Reads input, processes commands,
 * and executes them in a loop until the user exits.
 * Handles both interactive and non-interactive modes.
 *
 * @information: Pointer to the information structure.
 * @arguments: Command-line arguments.
 * Return: Returns the exit status or error code.
 */
int customShell(CommandInfo *information, char **arguments)
{
	ssize_t inputLength = 0;
	int builtinReturn = 0;

	while (inputLength != -1 && builtinReturn != -2)
	{
		information_clear(information);

		if (isInteractiveShell(information))
			print_str("$ ");

		error_print_char(BUFFER_F);
		inputLength = checkInput(information);

		if (inputLength != -1)
		{
			information_setter(information, arguments);
			builtinReturn = executeBuiltIn(information);

			if (builtinReturn == -1)
				findAndExecuteCommand(information);
		}
		else if (isInteractiveShell(information))
			print_char('\n');

		information_free(information, 0);
	}

	history_writing(information);
	information_free(information, 1);

	if (!isInteractiveShell(information) && information->execution_status)
		exit(information->execution_status);

	if (builtinReturn == -2)
	{
		if (information->error_number == -1)
			exit(information->execution_status);
		exit(information->error_number);
	}
	return (builtinReturn);
}
