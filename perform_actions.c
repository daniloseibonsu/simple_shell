#include "niichar_shell.h"

/**
 * perform_actions - This is a function to execute  entered commands
 *
 * @parsed_arguments: a variable parsed  inputted  arguments
 */

void perform_actions(char **parsed_arguments)
{
	char *full_command_path;

	if (is_niichar_path_available(parsed_arguments[0]) == 1)
	{
		niichar_do_system_call(parsed_arguments[0], parsed_arguments);
	}
	else
	{
		full_command_path = get_command_path(parsed_arguments[0]);
		niichar_do_system_call(full_command_path, parsed_arguments);
		free(full_command_path);
	}
}

/**
 * niichar_do_system_call - a function to execute entered commands
 *
 * @command_to_execute: an actual command to be executed
 *
 * @parsed_arguments: parsed  inputted arguments
 */
void niichar_do_system_call(char *command_to_execute, char **parsed_arguments)
{
	pid_t niichar_process_id;
	char *imploded_command;

	if (command_to_execute != NULL)
	{
		niichar_process_id = fork();
		if (niichar_process_id == 0)
		{
			execve(command_to_execute, parsed_arguments, NULL);
			perror(niichar_shell_name);
		}
		else if (niichar_process_id < 0)
		{
			perror(strcat(niichar_shell_name, " :1 : "));
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		imploded_command = niichar_implode(parsed_arguments, " ");
		niichar_write_error(imploded_command);
		free(imploded_command);
	}
}

/**
 * is_niichar_path_available - this function
 * checks if the supplied command path is available
 *
 * @full_command_path: pulls the command full path
 *
 * Return: Returns an integer
 */
int is_niichar_path_available(char *full_command_path)
{
	int is_available = 0;

	if (access(full_command_path, F_OK) == 0 &&
			access(full_command_path, X_OK) == 0)
	{
		is_available = 1;
	}
	return (is_available);
}

/**
 * niichar_write_error - this function prints the error message to stderr
 *
 * @imploded_command: this function points to command as string
 *
 * Return: Returns an integer
 */
int niichar_write_error(char *imploded_command)
{
	char *error_message;

	error_message = malloc(NIICHAR_MAX_BUFFER_SIZE * sizeof(char));

	if (error_message == NULL)
	{
		perror(niichar_shell_name);
		return (1);
	}

	snprintf(error_message, 1024,
			"%s: 1: %s: command not found\n",
			niichar_shell_name, imploded_command);

	write(STDERR_FILENO, error_message, strlen(error_message));
	free(error_message);

	return (0);
}
