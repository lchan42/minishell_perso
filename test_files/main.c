#include "../minishell.h"

int main ()
{
	char *read;
	read = NULL;

	while (!read)
	{
		read = readline("minishell: ");
		if (read)
			while (!*read)
			{
				free(read);
				read = readline("minishell: ");
			}
	}
	free(read);
}
