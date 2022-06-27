/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/06/27 19:43:08 by lchan            ###   ########.fr       */
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

void	__visual_print_t_list(t_list *lst)
{
	while (lst)
	{
		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("index = %d\n", ((t_lexer_token *)lst->content)->type);
		printf("index = %s\n", ((t_lexer_token *)lst->content)->start);
		printf("index = %s\n", ((t_lexer_token *)lst->content)->end);
		printf("index = %ld\n", ((t_lexer_token *)lst->content)->length);
		printf("\n");
		lst = lst->next;
	}
}


int main (int ac, char **av, char **envp)
{
	char *read;
	(void) ac;
	(void) av;
	(void) envp;
	char *start;
	char *end;

 	read = readline("test : ");
	start = read;
	end = read;
	while (*start)
	{
		lexer_set_ptrs(&start, &end);
		write(1, start, end - start);
		write(1, "\n", 1);
		printf("start%p\n", start);
		printf("start%p\n", end);
		printf("%ld\n", end - start);
		write(1, "\n", 1);
		start = end;
	}
	// printf("start = %s\n", start);
	// printf("end = %s\n", end);
	// start = end;
	// 	lexer_reader(&start, &end);
	// printf("start = %s\n", start);
	// printf("end = %s\n", end);
	// start = end;
	// 		lexer_reader(&start, &end);
	// printf("start = %s\n", start);
	// printf("end = %s\n", end);
	free(read);
	//free(token_tab);
}

/*
t_list	*lexer(char *str)
{
	t_list	*head;
	char	*str_end;

	str_end = str + ft_strlen(str);
	head = NULL;
	lexer_reader(str, head, str_end);
}*/
// print *((t_lexer_token *)head->content)) in lldb.
