/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:05:05 by lchan             #+#    #+#             */
/*   Updated: 2022/07/18 17:24:44 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int __get_redir_type(t_lexer_token *redir)
// {
// 	if (*(redir->start) == '<')
// 	{
// 		if (redir->length == 2)
// 			return (HERE_D);
// 		else
// 			return (IN_D);
// 	}
// 	else
// 	{
// 		if (redir->length == 2)
// 			return (OUT_D);
// 		else
// 			return (OUT_D_APP);
// 	}
// }

// static char *__get_arg(t_lexer_token *word, int type)
// {
// 	char *arg;
// 	char *tmp;

// 	arg = ft_calloc(sizeof(char), (word->length + 1));
// 	printf("calloc address = %p\n", arg);
// 	tmp = word->start;
// 	if (type != HERE_D && word->length > 255)
// 		return (0); // add error return message "filename too long"
// 	while (tmp != word->end)
// 	{
// 		printf("tmp -->%c ", *tmp);
// 		*(arg++) = *(tmp++);
// 		printf("arg -->%c ", *(arg - 1));
// 	}
// 	*(arg)= '\0';
// 	return (arg - (word->length));
// }

// static int	__pars_input_token(t_io **in, t_llist *redir, t_llist *word)
// {
// 	if (word)
// 	{
// 		(*in)->type = __get_redir_type((t_lexer_token *)(redir->content));
// 		if ((*in)->arg)
// 		 	free((*in)->arg);
// 		(*in)->arg = __get_arg((t_lexer_token *)(word->content), (*in)->type);
// 		printf("ICI %s\n", (*in)->arg);
// 		return (1);
// 	}
// 	else
// 		return (0); // add error message "unexpected token"
// }

// static void __init_in(t_io **in, t_llist *lexer)
// {
// 	if (!(*in))
// 		*in = ft_calloc(1, sizeof(t_io));
// 	while (lexer)
// 	{
// 		if (((t_lexer_token *)lexer->content)->type == TYPE_LEXER_OPERATOR_REDIRECT)
// 		{
// 			if (__pars_input_token(in, lexer, lexer->next))
// 				lexer = lexer->next;
// 			else
// 			{
// 				printf("ERROR EXPECTED\n");
// 				return ;
// 			}
// 		}
// 		lexer = lexer->next;
// 	}
// }

static t_llist	*__lexer_mover(t_llist *lexer, int type)
{
	if  (((t_lexer_token *)lexer)
 		&& ((t_lexer_token *)lexer->content)->type == type)
			lexer = lexer->next;
	while (((t_lexer_token *)lexer)
 		&& ((t_lexer_token *)lexer->content)->type != type)
		lexer = lexer->next;
	if  (((t_lexer_token *)lexer)
 		&& ((t_lexer_token *)lexer->content)->type == type)
			lexer = lexer->next;
	return (lexer);
}

static t_splcmd *__init_splcmd_node(t_splcmd **head, t_splcmd *runner)
{
	t_splcmd *new_node;

	new_node = ft_calloc(1, sizeof(t_splcmd));
	if (!(*head))
		*head = new_node;
	else
		runner->next = new_node;
	return (new_node);
}



t_splcmd	*__parser(t_llist *lexer)
{
	t_splcmd	*runner;
	t_splcmd	*head;

	runner = NULL;
	head = NULL;
	while (lexer)
	{
		runner = __init_splcmd_node(&head, runner);
		__init_io(&(runner->in), &(runner->out), lexer);
		//__init_cmd(&(runner->in), lexer);
		//__visual_print_lexer(lexer);
		lexer = __lexer_mover(lexer, TYPE_LEXER_OPERATOR_LOGICAL);
	}
	__visual_print_splcmd(head);
	__free_parse(&head);
	return (head);
}
