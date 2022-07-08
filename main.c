/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 19:52:11 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__visual_print_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
		while (tab[++i])
			printf("%d : %s\n",i , tab[i]);
}

void	__visual_print_lexer(t_list *lst)
{
	if (!lst)
		printf("lst address = %p\n", lst);
	while (lst)
	{
		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("type = %d\n", ((t_lexer_token *)lst->content)->type);
		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1, "[", 1);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		write(1, "]", 1);
		printf("\n\n");
		lst = lst->next;

	}
}

void	__visual_print_read_lst(t_list *read)
{
	printf("read str = [");
	while (read)
	{
		printf("%s", (char *)read->content);
		if (read->next)
			printf(" ");
		read = read->next;
	}
	printf("]\n");
}

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

