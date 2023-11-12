#include "niichar_shell.h"

/**
 *initiate_niichar_interactive - Starts the niichar_shell in interactive mode
 *
 * Return: void
 *
 */

void initiate_niichar_interactive(void)
{
	char *command_input;
	size_t niichar_linecap = 0;
	int shell_status = 1;
	char **parsed_command;
	ssize_t getline_result;

	while (shell_status == 1)
	{
		printf("$ ");

		getline_result = getline(&command_input, &niichar_linecap, stdin);

		if (getline_result == -1)
		{
			free(command_input);
			shell_status = -1;
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (!niichar_is_white_space(command_input))
			{
				parsed_command = parse_command_input(command_input, NIICHAR_TKN_SEPARATOR);
				if (parsed_command[0][0] != '#')
					execute_niichar_command(parsed_command);
				niichar_free_command_memory(parsed_command);
			}
		}
	}

	/* free(command_input); */
}
