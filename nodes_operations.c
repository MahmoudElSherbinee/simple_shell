#include "shell.h"
/**
* addNodeToList - function adds a new node to
* the beginning of a linked list.
*
* This function adds a new node to the beginning of a linked list. It allocates
* memory for the new node, initializes its fields, and updates the head of the
* linked list to point to the new node. The 'n' parameter is used to set the
* numerical value in the new node, and the 'str' parameter is used to set the
* string value (if provided).
*
* @head: A pointer to the head of the linked list.
* @str: The string value for the new node (can be NULL).
* @n: The numerical value for the new node.
*
* Return: Returns a pointer to the new node or NULL on failure.
*/
StringList *addNodeToList(StringList **head, const char *str, int n)
{
	StringList *newNode;

	/* Step 1: Check if 'head' is NULL */
	if (!head)
		return (NULL);

	/* Step 2: Allocate memory for the new node */
	newNode = malloc(sizeof(StringList));
	if (!newNode)
		return (NULL);

	/* Step 3: Initialize the new node and set its numerical value */
	fillMemoryBlock((void *)newNode, 0, sizeof(StringList));
	newNode->number = n;

	/* Step 4: Copy the string value (if provided) */
	if (str)
	{
		newNode->string = str_duplicate(str);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}

	/* Step 5: Update the next pointer of the new node to the current head */
	newNode->next = *head;

	/* Step 6: Update the head of the linked list to point to the new node */
	*head = newNode;

	/* Step 7: Return a pointer to the new node */
	return (newNode);
}

/**
* addNodeToEndOfList - function adds a new node
* to the end of a linked list.
*
* This function adds a new node to the end of a linked list. It allocates
* memory for the new node, initializes its fields, and appends the new node
* to the end of the linked list. The 'n' parameter is used to set the
* numerical value in the new node, and the 'str' parameter is used to set the
* string value (if provided).
*
* @head: A pointer to the head of the linked list.
* @str: The string value for the new node (can be NULL).
* @n: The numerical value for the new node.
*
* Return: Returns a pointer to the new node or NULL on failure.
*/
StringList *addNodeToEndOfList(StringList **head, const char *str, int n)
{
	StringList *newNode, *node;

	/* Step 1: Check if 'head' is NULL */
	if (!head)
		return (NULL);

	/* Step 2: Get a reference to the head of the linked list */
	node = *head;

	/* Step 3: Allocate memory for the new node */
	newNode = malloc(sizeof(StringList));
	if (!newNode)
		return (NULL);

	/* Step 4: Initialize the new node and set its numerical value */
	fillMemoryBlock((void *)newNode, 0, sizeof(StringList));
	newNode->number = n;

	/* Step 5: Copy the string value (if provided) */
	if (str)
	{
		newNode->string = str_duplicate(str);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}

	/* Step 6: Append the new node to the end of the linked list */
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	/* Step 7: Return a pointer to the new node */
	return (newNode);
}

/**
* findNodeWithPrefix - function finds the first node
* whose string starts with a given prefix.
*
* This function iterates through a linked list of strings, searching for the
* first node whose string starts with the specified 'prefix'. It also checks if
* the character immediately following the prefix matches the specified 'c' (or
* any character if 'c' is -1). If a match is found, the function returns a
* pointer to the matching node; otherwise, it returns NULL.
*
* @head: A pointer to the head of the linked list.
* @prefix: The prefix to search for in the strings.
* @c: The character to match immediately following the prefix (-1 for any).
*
* Return: Returns a pointer to the first matching node or NULL if not found.
*/
StringList *findNodeWithPrefix(StringList *head, char *prefix, char c)
{
	char *substringStart = NULL;

	/* Step 1: Iterate through the linked list */
	while (head)
	{
		/* Check if the string in the node starts with the specified prefix */
		substringStart = checkIfPrefix(head->string, prefix);

		/* Step 3: Check if the prefix is found and the character after it matches */
		if (substringStart && ((c == -1) || (*substringStart == c)))
			return (head);

		/* Step 4: Move to the next node in the linked list */
		head = head->next;
	}

	/* Step 5: Return NULL if no matching node is found */
	return (NULL);
}

#include <stddef.h>

/**
* getNodeIndexInList - function gets the index of a node within a linked list.
*
* This function calculates the index of a specified 'node' within a linked list
* It iterates through the linked list until it finds the target node andreturns
* its index. If the node is not found, it returns -1.
*
* @head: A pointer to the head of the linked list.
* @node: The target node whose index is to be determined.
*
* Return: Returns the index of the node or -1 if the node is not found.
*/
ssize_t getNodeIndexInList(StringList *head, StringList *node)
{
	size_t index = 0;

	/* Step 1: Iterate through the linked list */
	while (head)
	{
		/* Step 2: Check if the current node matches the target node */
		if (head == node)
			return (index);

		/* Step 3: Move to the next node in the linked list */
		head = head->next;

		/* Step 4: Increment the index */
		index++;
	}

	/* Step 5: Return -1 if the target node is not found */
	return (-1);
}

/**
* deleteNodeAtIndexInList - function deletes a node
* at a specified index in a linked list.
*
* This function deletes a node at the specified 'index' in a linked list. If
* the index is valid, it removes the corresponding node by adjusting pointers
* and freeing memory. The 'head' pointer is updated accordingly.
*
* @head: A pointer to the head of the linked list.
* @index: The index of the node to be deleted.
*
* Return: Returns 1 if the node is successfully deleted, 0 otherwise.
*/
int deleteNodeAtIndexInList(StringList **head, unsigned int index)
{
	StringList *currentNode, *previousNode;
	unsigned int currentIndex = 0;

	/* Step 1: Check if 'head' is NULL or the linked list is empty */
	if (!head || !*head)
		return (0);

	/* Step 2: Check if the node to be deleted is the first node (index 0) */
	if (!index)
	{
		currentNode = *head;
		*head = (*head)->next;
		free(currentNode->string);
		free(currentNode);
		return (1);
	}

	/* Step 3: Traverse the linked list to find the node at the specified index */
	currentNode = *head;
	while (currentNode)
	{
		/* Step 4: Check if the current index matches the target index */
		if (currentIndex == index)
		{
			previousNode->next = currentNode->next;
			free(currentNode->string);
			free(currentNode);
			return (1);
		}

		/* Step 5: Move to the next node in the linked list */
		currentIndex++;
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	/* Step 6: Return 0 if the specified index is out of bounds */
	return (0);
}
