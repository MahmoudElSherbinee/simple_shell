#include "shell.h"

/**
 * executeBuiltIn - function executes a built-in command if available.
 *
 * Searches for the specified command in the built-in command table
 * and executes the corresponding built-in function if found.
 *
 * @information: Pointer to the information structure.
 * Return: The return value of the executed built-in function,
 * or -1 if the command is not built-in.
 */
int executeBuiltIn(CommandInfo *information)
{
	int index, builtInResult = -1;

	BuiltinTable my_builtIn_table[] = {
		{"exit", exit_command},
		{"env", printEnvironmentVariables},
		{"help", help_command},
		{"history", print_command_history},
		{"setenv", SetCustomEnvironment},
		{"unsetenv", UnsetCustomEnvironment},
		{"cd", changeDirectory_command},
		{"alias", alias_custom},
		{NULL, NULL}
		};

	for (index = 0; my_builtIn_table[index].command_type; index++)
	{
		if (str_compare(information->arguments_array[0],
						my_builtIn_table[index].command_type) == 0)
		{
			information->current_line++;
			builtInResult = my_builtIn_table[index].command_function(information);
			break;
		}
	}

	return (builtInResult);
}
