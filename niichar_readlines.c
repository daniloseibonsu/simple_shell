#include "niichar_shell.h"

/**
 * niichar_read_lines - This function reads the lines from a file or a stdin
 *
 * Return: Returns a pointer to lines read as a string
 */

char *niichar_read_lines(void)
{
	char *input_commands = NULL;
	size_t niichar_buffer_size = 0;

	if (getline(&input_commands, &niichar_buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input_commands);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(input_commands);
			perror(niichar_shell_name);
			exit(EXIT_FAILURE);
		}
	}
	return (input_commands);
}
