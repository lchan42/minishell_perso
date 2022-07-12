/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/07/12 13:05:32 by lchan            ###   ########.fr       */
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
void	lexer_readline(char **usr_input, char *prompt)
{
	while (!*usr_input)
	{
		*usr_input = readline(prompt);
		if (**usr_input == '\0')
		{
			free(*usr_input);
			*usr_input = NULL;
		}
	}
}

void	lexer_loop(t_lexer_data *l_data)
{
	char *usr_input;

	usr_input = NULL;
	if (l_data->read_lst == NULL)
		lexer_readline(&usr_input, FIRST_PROMPT);
	else
		lexer_readline(&usr_input, LEXER_PROMPT);
	ft_lstadd_back(&l_data->read_lst, ft_lstnew(usr_input));
	lexer_make(l_data, usr_input);
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
	//char *usr_input;
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

