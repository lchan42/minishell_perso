/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_visual.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:10 by lchan             #+#    #+#             */
/*   Updated: 2022/07/15 12:57:12 by lchan            ###   ########.fr       */
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

void	__visual_print_lexer(t_llist *lst)
{
	if (!lst)
		printf("lst address = %p\n", lst);
	while (lst)
	{
//		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("type = %d\n", ((t_lexer_token *)lst->content)->type);
//		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
//		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
//		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1, "[", 1);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		write(1, "]", 1);
		printf("\n\n");
		lst = lst->next;
	}
}

void	__reverse_visual_print_lexer(t_llist *lst)
{
	if (!lst)
		printf("lst address = %p\n", lst);
	while (lst->next)
		lst = lst->next;
	while (lst)
	{
//		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("type = %d\n", ((t_lexer_token *)lst->content)->type);
//		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
//		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
//		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1, "[", 1);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		write(1, "]", 1);
		printf("\n\n");
		lst = lst->prev;
	}
}

void	__visual_print_read_lst(t_llist *usr_input)
{
	printf("usr_input str = [");
	while (usr_input)
	{
		printf("%s", (char *)usr_input->content);
		if (usr_input->next)
			printf(" ");
		usr_input = usr_input->next;
	}
	printf("]\n");
}
