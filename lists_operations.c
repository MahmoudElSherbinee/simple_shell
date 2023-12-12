#include "shell.h"

/**
* printLinkedListStrings - function prints the strings
* in a linked list of structures.
*
* This function prints the strings contained in a linked list of structures.
* It iterates through the linked list, printing each string or "(nil)" if
* the string is NULL. It returns the number of nodes in the linked list.
*
* @head: A pointer to the head of the linked list.
*
* Return: Returns the number of nodes in the linked list.
*/
size_t printLinkedListStrings(const StringList *head)
{
	size_t count = 0;

	/* Step 1: Iterate through the linked list */
	while (head)
	{
		/* Step 2: Print the string or "(nil)" if the string is NULL */
		print_str(head->string ? head->string : "(nil)");
		print_str("\n");

		/* Step 3: Move to the next node in the linked list */
		head = head->next;

		/* Step 4: Increment the count of nodes */
		count++;
	}

	/* Step 5: Return the number of nodes in the linked list */
	return (count);
}

/**
* freeLinkedList - function frees the memory
* occupied by a linked list of structures.
*
* This function frees the memory occupied by a linked list of structures,
* including the memory for each string ('string') within the structures.
* It takes a pointer to the head of the linked list ('headPtr') and frees
* the memory for each node in the list. After freeing the memory, it sets
* the head pointer to NULL.
*
* @headPtr: A pointer to the head of the linked list.
*/
void freeLinkedList(StringList **headPtr)
{
	StringList *node, *nextNode, *head;

	/* Step 1: Check if 'headPtr' or '*headPtr' is NULL */
	if (!headPtr || !*headPtr)
		return;

	/* Step 2: Set 'head' to the value of '*headPtr' */
	head = *headPtr;

	/* Step 3: Iterate through the linked list and free the memory */
	node = head;
	while (node)
	{
		nextNode = node->next;

		/* Step 4: Free the memory for the string within the structure */
		free(node->string);

		/* Step 5: Free the memory for the structure itself */
		free(node);

		/* Step 6: Move to the next node in the linked list */
		node = nextNode;
	}

	/* Step 7: Set the head pointer to NULL */
	*headPtr = NULL;
}

/**
* getLinkedListLength - function returns the number of nodes in a linked list.
*
* This function returns the number of nodes in a linked list. It takes a
* pointer to the head of the linked list ('head') and iterates through the
* list, incrementing a counter for each node encountered. The final count
* represents the number of nodes in the linked list.
*
* @head: A pointer to the head of the linked list.
*
* Return: Returns the number of nodes in the linked list.
*/
size_t getLinkedListLength(const StringList *head)
{
	size_t count = 0;

	/* Step 1: Iterate through the linked list and count the nodes */
	while (head)
	{
		/* Step 2: Move to the next node in the linked list */
		head = head->next;

		/* Step 3: Increment the count of nodes */
		count++;
	}

	/* Step 4: Return the number of nodes in the linked list */
	return (count);
}


/**
* printLinkedList - function prints the elements of a linked list
* containing numerical values and strings.
*
* This function prints the elements of a linked list, where each element
* consists of a numerical value ('num') and a string ('str'). It uses the
* 'convertLongToBaseString' function to convert the numerical value to a string
* representation before printing. The format for each element is "num: str\n".
* If 'str' is NULL, it prints "(nil)" in place of the string.
*
* @head: A pointer to the head of the linked list.
*
* Return: Returns the number of nodes in the linked list.
*/
size_t printLinkedList(const StringList *head)
{
	size_t count = 0;

	/* Step 1: Iterate through the linked list and print each element */
	while (head)
	{
		/* Step 2: Convert the numerical value to a string and print it */
		print_str(conver_longInt_str(head->number, 10, 0));
		print_char(':');
		print_char(' ');

		/* Step 3: Print the string or "(nil)" if the string is NULL */
		print_str(head->string ? head->string : "(nil)");

		/* Step 4: Print a newline character */
		print_str("\n");

		/* Step 5: Move to the next node in the linked list */
		head = head->next;

		/* Step 6: Increment the count of nodes */
		count++;
	}

	/* Step 7: Return the number of nodes in the linked list */
	return (count);
}
