#ifndef NIICHAR_SHELL_H
#define NIICHAR_SHELL_H

#define NIICHAR_TOKEN_BUFFER_SIZE 64
#define NIICHAR_MAX_BUFFER_SIZE 1024
#define NIICHAR_TKN_SEPARATOR " \n\a\t\r"

/* HEADER FILES */
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stddef.h>

/* PROTOTYPES */
int is_niichar_interactive(void);
void initiate_niichar_interactive(void);
void initiate_niichar_non_interactive(void);
char **parse_command_input(char *command_input, char *niichar_separator);
void perform_actions(char **parsed_arguments);
char *get_command_path(char *command);
char *niichar_implode(char **splitted_tokens, char *needle);
void execute_niichar_command(char **parsed_command);
char *niichar_read_lines(void);
int niichar_is_white_space(char *input_string);
char *niichar_str_tokenizer(char *input_string, const char *separator);
int niichar_echo(char **parsed_commands);
int is_niichar_path_available(char *full_command_path);
int niichar_write_error(char *imploded_command);
void niichar_free_command_memory(char **parsed_command);
void niichar_do_system_call(char *command_to_execute, char **parsed_arguments);
void niichar_handle_file(char *file_name);
void niichar_process_file(char *file_name);

/* NIICHAR_BUILT_IN_FUNCTIONS */
int niichar_exit(char **parsed_command);
int niichar_env(char **parsed_command);
int niichar_cd(char **parsed_command);

extern char **environ;
char *niichar_shell_name;

typedef int (*Command)(char **args);

/**
 *struct built_in - basic info
 *
 * @name:is the  name of command
 *
 * @command: a pointer to command
 *
 */
typedef struct built_in
{
	    char *name;
		Command command;
} BuiltIn;

#endif /* NIICHAR_SHELL_H */
