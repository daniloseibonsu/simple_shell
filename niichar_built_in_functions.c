#include "niichar_shell.h"

/**
 *niichar_exit - The function to implement in-built exit
 *
 *@parsed_commands: Executed parsed command
 *
 * Return: Returns an int on success
 *
 */

int niichar_exit(char **parsed_commands)
{
	int exit_status;
	char *error_message;

	if (parsed_commands[1])
	{
		exit_status = atoi(parsed_commands[1]);
		if (exit_status < 0)
		{
			error_message = malloc(NIICHAR_MAX_BUFFER_SIZE * sizeof(char));

			if (error_message == NULL)
			{
				perror(niichar_shell_name);
				return (1);
			}

			snprintf(error_message, 1024,
					"%s: 1: %s: Illegal number: %d\n",
					niichar_shell_name, "exit", exit_status);

			write(STDERR_FILENO, error_message, strlen(error_message));
			free(error_message);
		}
		else
			exit(exit_status);
		return (exit_status);
	}
	else
	{
		exit(0);
		return (0);
	}
}

/**
 *niichar_env - The function to implement in-built env
 *
 *@parsed_commands: Executed parsed command
 *
 * Return: Returns an int on success
 *
 */

int niichar_env(char **parsed_commands __attribute__((unused)))
{
	int niichar_counter = 0;

	while (environ[niichar_counter] != NULL)
	{
		printf("%s\n", environ[niichar_counter]);
		niichar_counter++;
	}

	return (niichar_counter);
}

/**
 *niichar_cd - The function to implement in-built cd
 *
 *@parsed_commands: Executed parsed command
 *
 * Return: Returns an int on success
 *
 */

int niichar_cd(char **parsed_commands)
{
	char niichar_previous_dir[1024];

	getcwd(niichar_previous_dir, sizeof(niichar_previous_dir));

	if (parsed_commands[1] == NULL)
	{
		parsed_commands[1] = getenv("HOME");
	}
	else if (strcmp(parsed_commands[1], "-") == 0)
	{
		parsed_commands[1] = getenv("OLDPWD");
		if (parsed_commands[1] == NULL)
		{
			perror(niichar_shell_name);
			return (1);
		}
	}

	if (chdir(parsed_commands[1]) != 0)
	{
		perror(niichar_shell_name);
	}
	else
	{
		setenv("OLDPWD", niichar_previous_dir, 1);
		setenv("PWD", parsed_commands[1], 1);
	}
	return (0);
}

/**
 *niichar_echo - The function to implement in-built echo
 *
 *@parsed_commands: Executed parsed command
 *
 * Return: Returns an int on success
 */

int niichar_echo(char **parsed_commands)
{
	int niichar_process_id;

	if (parsed_commands[2])
		write(2, "Too many arguments\n", 20);
	else
	{
		if (strcmp("$$", parsed_commands[1]) == 0)
		{
			niichar_process_id = getpid();
			printf("%i\n", niichar_process_id);
		}
		else if (strcmp("$?", parsed_commands[1]) == 0)
		{
			int niichar_exit_status;

			wait(&niichar_exit_status);

			printf("%d", niichar_exit_status);
		}
		else
		{
			printf("%s\n", parsed_commands[1]);
		}
	}

	return (0);
}
