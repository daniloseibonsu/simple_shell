#include "niichar_shell.h"

/**
 * niichar_implode - This function implodes
 * array of string into one single string
 *
 * @splitted_tokens: a pointer to  array of  tokens
 *
 * @needle: serves as a pointer to the needle
 *
 * Return: Returns a pointer to the imploded string
 */

char *niichar_implode(char **splitted_tokens, char *needle)
{
	char *imploded_string = malloc(0);
	int splitted_token_index = 0, byteSize = 0;

	while (splitted_tokens[splitted_token_index] != NULL)
	{
		byteSize = strlen(splitted_tokens[splitted_token_index])
			+ 1 + strlen(needle) + 1;
		imploded_string = realloc(imploded_string, byteSize);
		if (splitted_token_index > 0)
		{
			strcat(imploded_string, needle);
		}

		strcat(imploded_string, splitted_tokens[splitted_token_index]);
		splitted_token_index++;
	}

	return (imploded_string);
}
