/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/07/09 17:00:55 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
void	lexer_analyser(t_list *lexer)
{
	if(!lexer)
	{
		printf("leaving lexer\n");
		exit(1);
	}
}
*/
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

void	lexer_loop(t_lexer_data *l_data)
{
	char *read;

	read = NULL;
	if (l_data->read_lst == NULL)
		lexer_readline(&read, FIRST_PROMPT);
	else
		lexer_readline(&read, LEXER_PROMPT);
	ft_lstadd_back(&l_data->read_lst, ft_lstnew(read));
	lexer_make(l_data, read);
}

/*
void	lexer_add_history(t_list *read_lst)
{
	char	*full_str;

	full_str = (char *)read_lst->content;
	read_lst = read_lst->next;
	while (read_lst)
	{
		full_str = ft_strjoin(full_str, (char *)read_lst->content);
		read_lst = read_lst->next;
	}
	add_history(full_str);
	free(full_str);
	//if (full_str != read_lst)
	//	free(full_str);
}
*/

int main (int ac, char **av, char **envp)
{
	//char *read;
	(void) ac;
	(void) av;
	(void) envp;
	t_lexer_data	l_data;

	l_data.lexer = NULL;
	l_data.read_lst = NULL;
	//while (!l_data.lexer)
	lexer_loop(&l_data);
	//lexer_add_history(l_data.read_lst);
	__visual_print_lexer(l_data.lexer);
	__visual_print_read_lst(l_data.read_lst);
	if (l_data.read_lst)
		lexer_add_history(l_data.read_lst);
	lexer_data_free(&l_data);
}

