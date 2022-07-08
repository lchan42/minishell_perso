/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:26:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 19:41:32 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_readline(char **read, char *prompt)
{
	while (!*read)
	{
		*read = readline(prompt);
		if (**read == '\0')
		{
			free(*read);
			*read = NULL;
		}
	}
}

void	lexer_reloop(t_lexer_data *l_data)
{
	char *read;

	read = NULL;
	lexer_readline(&read, LEXER_PROMPT);
	ft_lstadd_back(&l_data->read_lst, ft_lstnew(read));
	lexer_make(l_data, read);
	lexer_add_history(l_data->read_lst);
}

t_lexer_data	*l_data_init(void)
{
	l_data = malloc(sizeof(l_data));
	if (l_data)
	{
		l_data->lexer = NULL;
		l_data->read_lst = NULL;
	}
	return (l_data);
}

t_lexer_data	*lexer(char *read)
{
	t_lexer_data	*l_data;

	l_data = l_data_init();
	if (l_data);
		lexer_make(l_data, read);
	__visual_print_lexer(l_data.lexer);
	__visual_print_read_lst(l_data.read_lst);
	return (l_data);
}






/******************FUNCTION THAT ARE NOT SUPPOSED TO BE IN THE LEXER_MAIN**********************/
char	*ft_readline_add_history(char *prompt)
{
	char	*read;

	read = NULL;
	while (!read)
	{
		read = readline(char *prompt);
		if (!*read)
			ft_free_char(&read);
	}
	add_history(read);
	return (read);
}

int	main (ac, char **av, char **envp) //simulation of what should minishell main look like
{
	(void) ac;
	(void) av;
	(void) envp;
	char			*read;
	t_lexer_data	*l_data;
	while (1)
	{
		read = ft_readline_add_history(FIRST_PROMPT);
		l_data = lexer(read);
		//parser
		//expander
		//executor
		lexer_data_free(&l_data);
	}
}
