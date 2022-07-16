/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:05:05 by lchan             #+#    #+#             */
/*   Updated: 2022/07/16 19:39:58 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// static t_llist	*__lexer_mover(t_llist *lexer)
// {
// 	if (((t_lexer_token *)lexer->prev)
// 		&& ((t_lexer_token *)lexer->prev->content)->type == TYPE_LEXER_OPERATOR_LOGICAL)
// 		lexer = lexer->next;
// 	while (1)
// 	{
// 		if (((t_lexer_token *)lexer->prev)
// 		&& ((t_lexer_token *)lexer->prev->content)->type == TYPE_LEXER_OPERATOR_LOGICAL)
// 		{
// 			break;
// 		}
// 		lexer = lexer->next;
// 		if (!lexer)
// 			break ;
// 	}
// 	return (lexer);
// }

static t_splcmd *__init_splcmd_node(t_splcmd **head, t_splcmd *runner)
{
	t_splcmd *new_node;

	new_node = ft_calloc(1, sizeof(t_splcmd));
	if (!(*head))
		*head = new_node;
	
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
		__visual_print_lexer(lexer);
		lexer = __lexer_mover(lexer, TYPE_LEXER_OPERATOR_LOGICAL);
	}
	return (NULL);
}
