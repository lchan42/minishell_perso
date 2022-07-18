/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:35:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/18 15:58:49 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list *__get_stock(t_list **stock, int type, char *arg)
{
	if (type == HERE_D)
}

static int __get_redir_type(t_lexer_token *redir)
{
	if (*(redir->start) == '<')
	{
		if (redir->length == 2)
			return (HERE_D);
		else
			return (IN_D);
	}
	else
	{
		if (redir->length == 2)
			return (OUT_D);
		else
			return (OUT_D_APP);
	}
}

static char *__get_arg(t_lexer_token *word, int type)
{
	char *arg;
	char *tmp;

	arg = ft_calloc(sizeof(char), (word->length + 1));
	if (!arg)
		return (NULL);
	tmp = word->start;
	if (type != HERE_D && word->length > 255)
		return (0); // add error return message "filename too long"
	while (tmp != word->end)
		*(arg++) = *(tmp++);
	*(arg)= '\0';
	return (arg - (word->length));
}

static int	__pars_io_token(t_io **io, t_llist *redir, t_llist *word)
{
	if (word)
	{
		(*io)->type = __get_redir_type((t_lexer_token *)(redir->content));
		//if ((*io)->arg)
		// 	free((*io)->arg);
		(*io)->arg = __get_arg((t_lexer_token *)(word->content), (*io)->type);
		(*io)->fd = (*io->type > 3);
		(*io)->stock = __get_stock(&((*io)->stock), (*io)->type, (*io)->arg);

		return (1);
	}
	else
		return (0); // add error message "unexpected token"
}

void __init_in(t_io **in, t_llist *lexer)
{
	if (!(*in))
		*in = ft_calloc(1, sizeof(t_io));
	while (lexer)
	{
		if (((t_lexer_token *)lexer->content)->type == TYPE_LEXER_OPERATOR_REDIRECT)
		{
			if (__pars_io_token(in, lexer, lexer->next))
				lexer = lexer->next;
			else
			{
				printf("ERROR EXPECTED\n");
				return ;
			}
		}
		lexer = lexer->next;
	}
}