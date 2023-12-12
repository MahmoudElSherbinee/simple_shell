#ifndef _SHELL_H_
#define _SHELL_H_

/* LIBRARIES */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stddef.h>
# include <bits/stat.h>
#include <linux/stat.h>

/*------------------------------------------------*/
/* Defines constants for specific conversion operations. */

#define CON_LOWER 1 /**< Identifier for converting to lowercase characters */
#define CON_UNS 2	/**< Identifier for converting to unsigned values */

/*------------------------------------------------*/
/* Defines constants representing different types of command chaining. */

#define COMMAND_NORMAL 0      /**< Represents normal command execution */
#define COMMAND_OR 1          /**< Represents logical OR chaining */
#define COMMAND_AND 2         /**< Represents logical AND chaining */
#define COMMAND_CHAIN 3       /**< Represents general command chaining */

/*------------------------------------------------*/
/* Defines constants to control the usage of specific functions. */

#define GETLINE 0	/**< Control flag for using the getline function */
#define STRTOK 0	/**< Control flag for using the strtok function */

/*------------------------------------------------*/
/* Buffers for reading and writing */

#define BUFFER_RD 1024
#define BUFFER_WR 1024
#define BUFFER_F -1
/*------------------------------------------------*/

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

/*------------------------------------------------*/
extern char **environ;
/*------------------------------------------------*/

/**
 * struct StringList - Represents a node in a linked list containing a string
 * and an associated number.
 *
 * This struct is commonly used for creating linked lists of strings
 * with corresponding numerical values.
 *
 * @number: Numeric value
 * @string: String value
 * @next: Pointer to the next node
 */
typedef struct StringList
{
	int number;				 /**< Numeric value associated with the string */
	char *string;			 /**< String value */
	struct StringList *next; /**< Pointer to the next node in the linked list */
} StringList;

/*------------------------------------------------*/


/**
 * struct CommandInfo - Represents information
 * related to a command within a shell.
 *
 * This struct encapsulates various details
 * such as command arguments, paths, history,and execution status,
 * providing a comprehensive view of the command's context.
 *
 * @argument: Command argument
 * @arguments_array: Array of command arguments
 * @executable_path: Path to the executable
 * @argument_count: Number of arguments
 * @current_line: Current line number
 * @error_number: Error number associated with the command
 * @linecount_indicator: Indicator for line count
 * @file_name: File name associated with the command
 * @environment_list: Linked list for environment variables
 * @command_history: Linked list for command history
 * @command_alias: Linked list for command aliases
 * @environment_variables: Array of environment variables
 * @environment_modified: Flag indicating environment modification
 * @command_buffer_type: Type of command: ||, &&, ;
 * @file_descriptor: File descriptor associated with the command
 * @history_count: Count of command history
 * @execution_status: Status of command execution
 * @command_buffer: Pointer to the command chain buffer for memory management
 */
typedef struct CommandInfo
{
	char *argument;				  /**< Command argument */
	char **arguments_array;		  /**< Array of command arguments */
	char *executable_path;		  /**< Path to the executable */
	int argument_count;			  /**< Number of arguments */
	unsigned int current_line;	  /**< Current line number */
	int error_number;			  /**< Error number associated with the command */
	int linecount_indicator;	  /**< Indicator for line count */
	char *file_name;			  /**< File name associated with the command */
	StringList *environment_list; /**< Linked list for environment variables */
	StringList *command_history;  /**< Linked list for command history */
	StringList *command_alias;	  /**< Linked list for command aliases */
	char **environment_variables; /**< Array of environment variables */
	int environment_modified;	  /**< ag indicating environment modification */
	int execution_status;		  /**< Status of command execution */
	/**< Pointer to the command chain buffer for memory management */
	char **command_buffer;
	int command_buffer_type;	  /**< Type of command: ||, &&, ; */
	int file_descriptor;		  /**< File descriptor associated with the command */
	int history_count;			  /**< Count of command history */
} CommandInfo;

#define COMMAND_INFO {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, \
NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
/*------------------------------------------------*/

/**
 * struct BuiltinTable - Represents a table entry for built-in shell commands.
 *
 * This struct defines an entry in a table of built-in shell commands.
 * Each entry includes a command type represented as a string and a function
 * pointer to the corresponding built-in command implementation.
 *
 * @command_type: representation of the built-in command type
 * @command_function: Function pointer to the built-in command implementation
 */
typedef struct BuiltinTable
{
	/**< String representation of the built-in command type */
	char *command_type;

	/**< Function pointer to the built-in command implementation */
	int (*command_function)(CommandInfo *);
} BuiltinTable;
/*------------------------------------------------*/
/* ///////// FUNCTIONS /////// */

/* status */
int isAlphabeticCharacter(int character);
int IfInDelimiterSet(char targetChar, char *delimiterSet);
int isInteractiveShell(CommandInfo *information);
int isCommand(CommandInfo *information, char *path);
int populateEnvironmentList(CommandInfo *information);
int populate_env_list(CommandInfo *info);

/* converters */
int convert_str_int(char *str);
char *conver_longInt_str(long int number, int base, int flags);
char **convert_list_arrstr(StringList *head);
int variables_replacer(CommandInfo *information);

/* printers */
int print_char(char character);
void print_str(char *inputString);
int print_int_fd(int integerValue, int fileDescriptor);
int print_char_fd(char character, int fileDescriptor);
int print_str_fd(char *inputString, int fileDescriptor);


/* error printers */
int error_str_to_int(char *str);
int error_print_char(char character);
void error_print_str(char *inputString);
void printErrorMessage(CommandInfo *fileInfo, char *errorString);


/* strings functions */
int str_length(char *inputString);
int str_compare(char *str1, char *str2);
char *char_in_str(char *searchString, char targetChar);
char *checkIfPrefix(const char *haystack, const char *needle);
int str_replacer(char **oldString, char *newString);

char *str_concatenate(char *destinationString, char *sourceString);
char *str_n_concatenate(char *destinationString, char *sourceString, int max);
char *str_copy(char *destinationString, char *sourceString);
char *str_n_copy(char *destinationString, char *sourceString, int max);
char *str_duplicate(const char *originalString);

/* builtin commands */
int exit_command(CommandInfo *information);
int changeDirectory_command(CommandInfo *information);
int help_command(CommandInfo *information);


/* str_tokens */
char **tokenizeString(char *str_in, char *delimiter);
char **tokenizeString_D(char *str_in, char delimiter);

/* memory_operations */
char *fillMemoryBlock(char *memoryBlock, char fillValue, unsigned int size);
void freeStringArray(char **stringArray);
int freeAndSetNull(void **memoryPtr);
void *realloc_Memory(void *oldPtr, unsigned int oldSize, unsigned int newSize);


/* lists */
size_t printLinkedListStrings(const StringList *head);
void freeLinkedList(StringList **headPtr);
size_t getLinkedListLength(const StringList *head);
size_t printLinkedList(const StringList *head);

/* nodes */
StringList *addNodeToList(StringList **head, const char *str, int n);
StringList *addNodeToEndOfList(StringList **head, const char *str, int n);
StringList *findNodeWithPrefix(StringList *head, char *prefix, char c);
ssize_t getNodeIndexInList(StringList *head, StringList *node);
int deleteNodeAtIndexInList(StringList **head, unsigned int index);


/* environment_operations */
char *getEnvironmentVariable(CommandInfo *information, const char *name);
int printEnvironmentVariables(CommandInfo *information);

char **getEnvironmentVariables(CommandInfo *information);

int setEnvironmentVariable(CommandInfo *information,
						   char *variable, char *value);
int unsetEnvironmentVariable(CommandInfo *information, char *variable);
int SetCustomEnvironment(CommandInfo *customInfo);
int UnsetCustomEnvironment(CommandInfo *customInfo);

/* remove comments */
void Comment_Remover(char *buffer);

/* aliases */
int alias_unsetter(CommandInfo *information, char *string);
int alias_setter(CommandInfo *information, char *string);
int alias_printer(StringList *node);
int alias_custom(CommandInfo *information);
int alias_replacer(CommandInfo *information);

/* chains */
int detectCommandChain(CommandInfo *information,
					   char *buffer, size_t *position);

void handleCommandChain(CommandInfo *information, char *buffer,
						size_t *position, size_t currentIndex, size_t bufferLength);


/* buffer operations */
ssize_t checkInput(CommandInfo *information);

ssize_t read_input_buffer(CommandInfo *information,
													char *buffer, size_t *index);

ssize_t input_buf(CommandInfo *info, char **buf, size_t *len);

ssize_t custom_getline(CommandInfo *information,
					   char **buffer, size_t *buffer_size);

/* command operationa */
void forkAndExecuteCommand(CommandInfo *information);
void findAndExecuteCommand(CommandInfo *information);
int customShell(CommandInfo *information, char **arguments);


/* information */
void information_setter(CommandInfo *information, char **arguments);
void information_clear(CommandInfo *information);
void information_free(CommandInfo *information, int all);

/* history */
char *history_getFile(CommandInfo *information);
int history_writing(CommandInfo *information);
int print_command_history(CommandInfo *information);

int history_buildList(CommandInfo *information, char *buffer, int line_count);
int history_reNumber(CommandInfo *information);
int history_reading(CommandInfo *information);


/* some other */
char *duplicate_characters(const char *path_str, int first, int end);
char *find_command_path(CommandInfo *information,
												char *path_str, char *command);



/* execution builtin */
int executeBuiltIn(CommandInfo *information);

/* main */
void handleSigInt(__attribute__((unused))int sigNum);

#endif /* SHELL_H*/
