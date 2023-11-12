#include "niichar_shell.h"

/**
 * niichar_handle_file - A function that handles parsed files
 *
 * @file_name: A pointer to hold the file name
 *
 * Return: void
 */

void niichar_handle_file(char *file_name)
{
	char **parsed_command;
	char niichar_file_buffer[NIICHAR_MAX_BUFFER_SIZE];
	ssize_t bytes_read;
	int file_handler = open(file_name, O_RDONLY);

	if (file_handler == -1)
	{
		perror("Error opening the file");
		return;
	}
	else
	{

		while ((bytes_read = read(file_handler,
						niichar_file_buffer, sizeof(niichar_file_buffer))) > 0)
		{

			niichar_file_buffer[bytes_read] = '\0';
			if (!niichar_is_white_space(niichar_file_buffer))
			{
				parsed_command = parse_command_input(niichar_file_buffer,
						NIICHAR_TKN_SEPARATOR);
				execute_niichar_command(parsed_command);
				niichar_free_command_memory(parsed_command);
			}
		}

		if (bytes_read == -1)
		{
			perror(niichar_shell_name);
			close(file_handler);
			return;
		}
	}

	close(file_handler);
}

/**
 * niichar_process_file - A function that processes file
 *
 * @file_name: A pointer to a filename
 *
 * Return: void
 */
void niichar_process_file(char *file_name)
{
	char *error_message;
	struct stat niichar_file_struct;

	if (access(file_name, F_OK) == -1)
	{
		error_message = malloc(NIICHAR_MAX_BUFFER_SIZE * sizeof(char));

		if (error_message == NULL)
		{
			perror(niichar_shell_name);
			exit(EXIT_FAILURE);
		}

		snprintf(error_message, NIICHAR_MAX_BUFFER_SIZE,
				"%s: 0: Can't open %s\n",
				niichar_shell_name, file_name);

		write(STDERR_FILENO, error_message, strlen(error_message));
		free(error_message);
		exit(127);
	}

	if (stat(file_name, &niichar_file_struct) == -1)
	{
		perror("Error getting file information");
		exit(EXIT_FAILURE);
	}

	if (niichar_file_struct.st_size == 0)
	{
		/* fprintf(stderr, "File is empty\n"); */
		exit(EXIT_SUCCESS);
	}

	niichar_handle_file(file_name);
}
