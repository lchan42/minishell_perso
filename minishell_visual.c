/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_visual.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:10 by lchan             #+#    #+#             */
/*   Updated: 2022/07/19 16:19:22 by lchan            ###   ########.fr       */
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

void	__visial_print_type(int type)
{
	const char	*type_str [] = {
	[TYPE_LEXER_WORD] = "word",
	[TYPE_LEXER_OPERATOR_LOGICAL] = "op logical",
	[TYPE_LEXER_OPERATOR_REDIRECT] = "op redirect",
	[TYPE_LEXER_SYNTAX_ERR] = "syntax error"
	};

	printf("type = %s (%d)\n", type_str[type], type);
}


void	__visual_print_lexer(t_llist *lst)
{
	if (!lst)
		printf("lst address = %p\n", lst);
	while (lst)
	{
//		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		//printf("type = %d (%s)\n", ((t_lexer_token *)lst->content)->type);
		__visial_print_type(((t_lexer_token *)lst->content)->type);
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


/*
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
*/

/******************PARSER VISUAL***************************/

void	__visial_parser_print_type(int type)
{
	const char	*type_str [] = {
	NULL,
	"IN _D",
	"HERE_D",
	"PIPE_IN",
	"OUT_D",
	"OUT_D_APP",
	"PIPE_OUT",
	};

	printf("		type = %s (%d)", type_str[type], type);
}

void	__visual_print_splcmd(t_splcmd *head)
{


	int  i = 1;
	while (head)
	{
		t_list *tmp_in_st = head->in.stock, *tmp_out_st = head->out.stock;
		printf("\t\t\t****************splcmd [%d]****************\n 		in_addr --> [%p] out_addr --> [%p] cmd_addr --> [%p]\n", i++, \
		&(head->in), &(head->out), &(head->cmd));

		// printf("\t\tin_type --> %-15d | out_type --> %-15d\n
		// in_arg  --> %-15s | out_arg  -->%-15s\n\n",
		// head->in.type, head->out.type,
		// head->in.arg, head->out.arg);
		__visial_parser_print_type(head->in.type);
		printf("\t \t");
		__visial_parser_print_type(head->out.type);

		printf("\n\n		-----IN_STOCK -->\n");
		for (int i = 0;(tmp_in_st);i++)
		{
			printf("\t\targ[%d] --> %s  |  ", i, (char *)(tmp_in_st->content));
			tmp_in_st = tmp_in_st->next;
		}
		printf("\n\n		----OUT_STOCK -->\n");
		for (int i = 0;(tmp_out_st);i++)
		{
			printf("\t\targ[%d] --> %s  |  ", i, (char *)(tmp_out_st->content));
			tmp_out_st = tmp_out_st->next;
		}
		puts("\n\n\n");
		head = head->next;
	}
}
