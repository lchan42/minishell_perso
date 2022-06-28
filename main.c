/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/06/28 19:21:06 by lchan            ###   ########.fr       */
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
	while (lst)
	{
		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("type = %d\n", ((t_lexer_token *)lst->content)->type);
		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		printf("\n\n");
		lst = lst->next;
	}
}

void	lexer_analyser(t_list *lexer)
{
	if(!lexer)
	{
		printf("leaving lexer\n");
		exit(1);
	}
}


/*********************eventual question to ask:
 * concerning odd quotes, do nothing ? or ask for completion ?
 * lexer nods, Show I seperate words according to METACHAR or space?
 */


/**********************to do
 * lexer analyser : checking the conformity of type operator
 * 					attributing types
 */

/**********************
 * interrogation: concerning the error control function
 * before the construction of the t_list
 * during the construction of the t_list
 * after the construction of the t_list
 */
int main (int ac, char **av, char **envp)
{
	char *read;
	(void) ac;
	(void) av;
	(void) envp;
	t_list *lexer;

 	read = get_next_line(0);				//using gnl here rather than readline coz less leak
	*(read + ft_strlen(read) - 1) = '\0';	//replacing the \n by \0
	lexer = lexer_make(read);
	lexer_analyser(lexer);
	__visual_print_lexer(lexer);
	lexer_free(lexer);

	free(read);
}
