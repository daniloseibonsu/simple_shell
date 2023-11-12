#include "niichar_shell.h"

/**
 * niichar_free_command_memory - This function
 * frees memory(prevents memory leaks).
 *
 * @parsed_command: A pointer to the  memory to be freed.
 *
 * Return: void
 */

void niichar_free_command_memory(char **parsed_command)
{
	int i;

	if (parsed_command != NULL)
	{
		for (i = 0; parsed_command[i] != NULL; i++)
		{
			free(parsed_command[i]);
		}

		free(parsed_command);
	}
}
