#include "shell.h"

/**
 * bfree - this frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if it is freed, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
