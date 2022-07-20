/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:05:05 by lchan             #+#    #+#             */
/*   Updated: 2022/07/20 12:11:00 by slahlou          ###   ########.fr       */
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

int	__parse_cmd_token(t_cmd *cmd, t_lexer_token *word)
{
	char *arg;
	char *tmp;

	arg = ft_calloc(sizeof(char), word->length + 1);
	if (!arg)
		return (-1);
	cmd->size += 1;
	tmp = word->start;
	while (tmp != word->end)
		*(arg++) = *(tmp++);
	*(arg)= '\0';
	arg -= word->length;
	ft_lstadd_back(&(cmd->cmd_lst), ft_lstnew(arg));
	return (0);
}

int __init_cmd(t_cmd *cmd, t_llist *lexer)
{
	//cmd->size = 0;
	while (lexer)
	{
		if (lexer && ((t_lexer_token *)lexer->content)->type == TYPE_LEXER_OPERATOR_REDIRECT)
			lexer = lexer->next->next;
		if (lexer && ((t_lexer_token *)lexer->content)->type == TYPE_LEXER_WORD)
		{
			if (__parse_cmd_token(cmd, ((t_lexer_token *)lexer->content)) == -1)
				return (-1);
			lexer = lexer->next;
		}
		if (lexer && ((t_lexer_token *)lexer->content)->type == TYPE_LEXER_OPERATOR_LOGICAL)
			break ;
	}
	return (0);
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
		if ((__init_io(&(runner->in), &(runner->out), lexer) == -1) \
		|| __init_cmd(&(runner->cmd), lexer) == -1)
		{
			__free_parse(&head);
			break ;
		}
		lexer = __lexer_mover(lexer, TYPE_LEXER_OPERATOR_LOGICAL);
	}
	// if (head)
	// 	__visual_print_splcmd(head);
	return (head);
}

