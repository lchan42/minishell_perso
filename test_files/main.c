#include "../minishell.h"

// a function to clear the wrong history list

int main ()
{
	char	*read_full;
	char	*prompt;
	t_list	*history_list;

	prompt = NULL;
	history_list = (t_list *)0;
	read_full = ft_strdup("");
	while (1)
	{
		prompt = readline("minishell: ");
		if (*(prompt + strlen(prompt) - 1) == '|')
		{
			rl_replace_line(read_full, 1);
			read_full = ft_strjoin(read_full , prompt);
			printf("Value of read_full %s\n", read_full);
		}
		add_history(read_full);
		//free(read);
	}
	//free(read);
}
