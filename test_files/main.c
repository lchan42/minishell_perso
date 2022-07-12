#include "minishell.h"

// a function to clear the wrong history list

// int main ()
// {
// 	char	*read_full;
// 	char	*prompt;
// 	t_list	*history_list;

// 	prompt = NULL;
// 	history_list = (t_list *)0;
// 	read_full = ft_strdup("");
// 	while (1)
// 	{
// 		prompt = readline("minishell: ");
// 		if (*(prompt + strlen(prompt) - 1) == '|')
// 		{
// 			//rl_on_new_line();
// 			readline(">: ");
// 			//rl_replace_line("", 0);
// 			//rl_redisplay();
// 			read_full = ft_strjoin(read_full , prompt);
// 			printf("Value of read_full %s\n", read_full);
// 		}
// 		add_history(read_full);
// 		free(read_full);
// 	}
// }

int main ()
{
	char *read;
	char *read_full;

	read = NULL;
	read_full = NULL;

	while (1)
	{
		read_full = readline ("minishell prompt: ");
		add_history (read_full);
		if (*(read_full + strlen(read_full) - 1) == '|')
		{
			rl_on_new_line();
			read = readline(">: ");
			rl_replace_line("", 0);
			rl_redisplay();
			read_full = ft_strjoin_free(read_full, read);
		}
		free(read_full);
	}

 }

// int	main ()
// {
// 	int	fd;

// 	fd = open("test", O_CREAT | O_EXCL | O_TRUNC);

// }
