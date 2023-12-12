#include "shell.h"
/**
 * handleSigInt - function - signal handler for SIGINT (Ctrl+C).
 *
 * This function is a signal handler for the SIGINT signal (Ctrl+C). It prints
 * a newline, the shell prompt, and flushes the output buffer.
 *
 * @sigNum: The signal number (not used in the function).
 */
void handleSigInt(__attribute__((unused)) int sigNum)
{
	/* Step 1: Print a newline */
	print_str("\n");

	/* Step 2: Print the shell prompt */
	print_str("$ ");

	/* Step 3: Flush the output buffer */
	print_char(BUFFER_F);
}

/**
 * main - function executes the main logic of the custom shell program.
 *
 * This function initializes necessary data structures,
 * handles file operations,
 * and interacts with the custom shell's core functionality.
 * It takes command-line
 * arguments, opens a file if specified, populates environment information,
 * reads command history, and invokes the custom shell engine.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: Returns EXIT_SUCCESS on successful execution,
 * or EXIT_FAILURE otherwise.
 */

int main(int argc, char **argv)
{
	CommandInfo information[] = {COMMAND_INFO};
	int file_descriptor = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(file_descriptor)
		: "r"(file_descriptor));

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_print_str(argv[0]);
				error_print_str(": 0: Can't open ");
				error_print_str(argv[1]);
				error_print_char('\n');
				error_print_char(BUFFER_F);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->file_descriptor = file_descriptor;
	}
	populateEnvironmentList(information);
	history_reading(information);
	customShell(information, argv);
	return (EXIT_SUCCESS);
}
