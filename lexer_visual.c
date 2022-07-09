/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_visual.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:10 by lchan             #+#    #+#             */
/*   Updated: 2022/07/09 17:01:19 by lchan            ###   ########.fr       */
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
