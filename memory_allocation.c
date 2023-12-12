#include "shell.h"

/**
* fillMemoryBlock - function fills a block of memory with a specified value.
*
* This function fills the first 'n' bytes of the memory area pointed to by
* 'memoryBlock' with the specified value 'fillValue'. It returns a pointer to
* the memory area.
*
* @memoryBlock: A pointer to the memory area to be filled.
* @fillValue: The value to be set in each byte.
* @size: The number of bytes to be filled with 'fillValue'.
*
* Return: Returns a pointer to the memory area.
*/
char *fillMemoryBlock(char *memoryBlock, char fillValue, unsigned int size)
{
	unsigned int i;

	/* Step 1: Fill the memory area with the specified value */
	for (i = 0; i < size; i++)
		memoryBlock[i] = fillValue;

	/* Step 2: Return a pointer to the memory area */
	return (memoryBlock);
}

/**
* freeStringArray - function frees the
* memory allocated for an array of strings.
*
* This function frees the memory allocated for an array of strings, including
* the memory for the array itself. It takes a pointer to the array of strings
* 'stringArray' and releases the memory for each string and the array itself.
* If 'stringArray' is NULL, the function returns without any action.
*
* @stringArray: A pointer to the array of strings to be freed.
*/
void freeStringArray(char **stringArray)
{
	char **tempPointer = stringArray;

	/* Step 1: Check if 'stringArray' is NULL */
	if (!stringArray)
		return;

	/* Step 2: Free the memory for each string in the array */
	while (*stringArray)
		free(*stringArray++);

	/* Step 3: Free the memory for the array itself */
	free(tempPointer);
}


/**
* freeAndSetNull - function frees the memory pointed to
* by a pointer and sets the pointer to NULL.
*
* This function frees the memory pointed to by the pointer 'memoryPtr' and
* sets the pointer to NULL. If 'memoryPtr' is NULL or the pointer itself is
* NULL, the function returns 0. If memory is successfully freed, it returns 1.
*
* @memoryPtr: A pointer to the memory to be freed.
*
* Return: Returns 1 if memory is freed successfully, 0 otherwise.
*/
int freeAndSetNull(void **memoryPtr)
{
	/* Step 1: Check if 'memoryPtr' and '*memoryPtr' are not NULL */
	if (memoryPtr && *memoryPtr)
	{
		/* Step 2: Free the memory and set the pointer to NULL */
		free(*memoryPtr);
		*memoryPtr = NULL;

		/* Step 3: Return 1 to indicate successful memory freeing */
		return (1);
	}

	/* Step 4: Return 0 to indicate that no memory was freed */
	return (0);
}

/**
* realloc_Memory - function reallocates memory for a block of memory.
*
* This function reallocates memory for a block of memory pointed to
* by 'oldPtr'.
* It resizes the memory block to 'newSize' bytes.
* If 'oldPtr' is NULL, it allocates a new memory block of size 'newSize'.
* If 'newSize' is zero, it frees the memory block pointed to
* by 'oldPtr' and returns NULL.
* If 'newSize' is equal to 'oldSize', it returns 'oldPtr' without any change.
* If reallocation fails, it returns NULL.
*
* @oldPtr: A pointer to the block of memory to be reallocated.
* @oldSize: The current size of the block of memory pointed to by 'oldPtr'.
* @newSize: The new size for the reallocated block of memory.
*
* Return: Returns a pointer to the reallocated block of memory.
*         Returns NULL if reallocation fails or 'newSize' is zero.
*/
void *realloc_Memory(void *oldPtr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	/* Step 1: Check if 'oldPtr' is NULL */
	if (!oldPtr)
		return (malloc(newSize));

	/* Step 2: Check if 'newSize' is zero */
	if (!newSize)
		return (free(oldPtr), NULL);

	/* Step 3: Check if 'newSize' is equal to 'oldSize' */
	if (newSize == oldSize)
		return (oldPtr);

	/* Step 4: Allocate memory for the new block */
	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);

	/* Step 5: Copy the contents from the old block to the new block */
	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)oldPtr)[oldSize];

	/* Step 6: Free the memory for the old block */
	free(oldPtr);

	/* Step 7: Return a pointer to the reallocated block of memory */
	return (newPtr);
}
