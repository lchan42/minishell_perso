/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:05:05 by lchan             #+#    #+#             */
/*   Updated: 2022/07/16 20:14:25 by lchan            ###   ########.fr       */
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

void __free_parse(t_splcmd **head)
{
	t_splcmd *runner;

	runner = *head;
	if (*head)
	{
		while (runner)
		{
			if (runner->in)
				free(runner->in);  // add ft_free_in to free what is inside in_struct
			if (runner->out)
				free(runner->out); // add ft_free_out to free what is inside out_struct
			if (runner->cmd)
				free(runner->cmd); // add ft_free_cmd to free what is inside cmd_struct
			runner = runner->next;
			free(*head);
			*head = runner;
		}
		*head = NULL;
	}
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
		//__init_in();
		__visual_print_lexer(lexer);
		lexer = __lexer_mover(lexer, TYPE_LEXER_OPERATOR_LOGICAL);
	}
	__visual_print_splcmd(head);
	__free_parse(&head);
	return (head);
}
