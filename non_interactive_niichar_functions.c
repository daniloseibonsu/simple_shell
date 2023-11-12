#include "niichar_shell.h"

/**
 *initiate_niichar_non_interactive - This function
 *starts the shell in a non_interactive mode
 *
 * Return: void
 *
*/

void initiate_niichar_non_interactive(void)
{
	char *command_inputs;
	char **parsed_command;

	while ((command_inputs = niichar_read_lines()) != NULL)
	{
		if (!niichar_is_white_space(command_inputs))
		{
			parsed_command = parse_command_input(command_inputs, NIICHAR_TKN_SEPARATOR);
			if (parsed_command[0][0] != '#')
				execute_niichar_command(parsed_command);
			niichar_free_command_memory(parsed_command);
		}
		free(command_inputs);
	}
}
