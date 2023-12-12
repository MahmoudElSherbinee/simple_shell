#include "shell.h"

/**
* exit_command - function handles the exit functionality.
*
* This function checks if there is an argument provided with the exit command.
* If an argument is present, it converts it to an integer using '_erratoi'.
* If the conversion is successful, it sets the error number and returns -2.
* If the conversion fails, it sets the execution_status to 2,
* prints an error message, and returns 1.
* If no argument is provided, it sets the error number to -1 and returns -2.
*
* @information: The information structure containing command details.
*
* Return: Returns -2 if the exit command is valid and an argument is provided.
*         Returns 1 if there is an error in the exit argument.
*         Returns -2 if no exit argument is provided.
*/
int exit_command(CommandInfo *information)
{
	int exitValue;

	if (information->arguments_array[1])
	{
		/*Convert the exit argument to an integer using 'error_str_to_int' */
		exitValue = error_str_to_int(information->arguments_array[1]);

		/* Step 3: Check for conversion failure */
		if (exitValue == -1)
		{
			information->execution_status = 2;
			printErrorMessage(information, "Illegal number: ");
			error_print_str(information->arguments_array[1]);
			error_print_char('\n');
			return (1); /* Return 1 for conversion failure */
		}

		/* Step 4: Set the error number and */
		/* return -2 for a valid exit command with an argument */
		information->error_number = exitValue;
		return (-2);
	}

	/* Step 5: Set the error number to -1 and */
	/* return -2 for a valid exit command without an argument */
	information->error_number = -1;
	return (-2);
}

/**
* changeDirectory_command - function changes the current working directory.
*
* This function changes the current working directory based on the provided
* command arguments. If no arguments are given, it changes to the home
* directory. If the argument is "-", it changes to the previous working
* directory. Otherwise, it attempts to change to the specified directory.
*
* @information: A pointer to the structure containing command arguments and
* environment information.
*
* Return: Returns 0 on success, 1 on failure.
*/
int changeDirectory_command(CommandInfo *information)
{
	char *currentDir, *targetDir, buffer[1024];

	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		print_str("TODO: >>getcwd failure emsg here<<\n");
	if (!information->arguments_array[1])
	{		targetDir = getEnvironmentVariable(information, "HOME=");
		if (!targetDir)
			chdirResult = chdir((targetDir =
											getEnvironmentVariable(information, "PWD=")) ? targetDir : "/");
		else
			chdirResult = chdir(targetDir);
	}
	else if (str_compare(information->arguments_array[1], "-") == 0)
	{
		if (!getEnvironmentVariable(information, "OLDPWD="))
		{	print_str(currentDir);
			print_char('\n');
			return (1);
		}
		print_str(getEnvironmentVariable(information, "OLDPWD="));
		print_char('\n');
		chdirResult = chdir((targetDir =
										getEnvironmentVariable(information, "OLDPWD=")) ? targetDir : "/");
	}
	else
		chdirResult = chdir(information->arguments_array[1]);
	if (chdirResult == -1)
	{	printErrorMessage(information, "can't cd to ");
		error_print_str(information->arguments_array[1]);
		error_print_char('\n');
	}
	else
	{	setEnvironmentVariable(information, "OLDPWD",
													getEnvironmentVariable(information, "PWD="));
		setEnvironmentVariable(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
* help_command - function Displays help information for the shell.
*
* This function displays help information for the shell. It currently
* acknowledges that the help call works but mentions that the function is not
* yet implemented.
*
* @information: A pointer to the structure containing command arguments and
* environment information.
*
* Return: Always returns 0.
*/
int help_command(CommandInfo *information)
{
	char **argArray;

	/* Step 1: Temporary workaround to avoid unused variable warning */
	argArray = information->arguments_array;

	/* Step 2: Display a message indicating the help call works */
	print_str("Help call works. Function not yet implemented.\n");

	/* Step 3: Temporary workaround to avoid unused variable warning */
	if (0)
		print_str(*argArray);

	/* Step 4: Always return 0 */
	return (0);
}
