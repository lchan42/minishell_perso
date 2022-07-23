/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:35:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/23 10:53:29 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__get_redir_type(t_lexer_token *redir)
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
			return (OUT_D_APP);
		else
			return (OUT_D);
	}
}

static char	*__get_arg(t_lexer_token *word, int type)
{
	char *arg;
	char *tmp;

	arg = ft_calloc(sizeof(char), (word->length + 2));
	if (!arg)
		return (NULL);
	tmp = word->start;
	while (tmp != word->end)
		*(arg++) = *(tmp++);
	*(arg)= '\0';
	if (type == OUT_D)
		*(arg + 1) = 'T';
	else if (type == OUT_D_APP)
		*(arg + 1) = 'A';
	return (arg - (word->length));
}

static int __pars_io_pipe(t_io *i_o, t_lexer_token *token, int pipe_io)
{
	if (token->type == TYPE_LEXER_OPERATOR_LOGICAL)
	{
		i_o->type = pipe_io;
		i_o->fd = (i_o->type > 3);
		return (1);
	}
	return (0);
}


static int	__pars_io_token(t_io *io, t_llist *redir, t_llist *word)
{
	if (word)
	{
		if (((t_lexer_token *)(word->content))->type == TYPE_LEXER_SYNTAX_ERR)
			return (-1);
		(io)->type = __get_redir_type((t_lexer_token *)(redir->content));
		(io)->arg = __get_arg((t_lexer_token *)(word->content), (io)->type);
		(io)->fd = ((io)->type > PIPE_IN);
		(io)->stock = __get_stock(io, (io)->type);
		return (1);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
}

int __pars_io(t_io *in, t_io *out, t_llist *lexer)
{
	int res;

	if (lexer->prev)
		__pars_io_pipe(in, ((t_lexer_token *)lexer->prev->content), PIPE_IN);
	while (lexer)
	{
		res = 0;
		if (((t_lexer_token *)lexer->content)->type == TYPE_LEXER_OPERATOR_REDIRECT \
		&& *(((t_lexer_token *)lexer->content)->start) == '<')
			res = __pars_io_token(in, lexer, lexer->next);
		else if (((t_lexer_token *)lexer->content)->type == TYPE_LEXER_OPERATOR_REDIRECT \
		&& *(((t_lexer_token *)lexer->content)->start) == '>')
			res = __pars_io_token(out, lexer, lexer->next);
		if (res == 1)
			lexer = lexer->next;
		else if (res == -1 || ((t_lexer_token *)lexer->content)->type == TYPE_LEXER_SYNTAX_ERR)
			return (-1);
		if (__pars_io_pipe(out, ((t_lexer_token *)lexer->content), PIPE_OUT))
			break ;
		lexer = lexer->next;
	}
	return (0);
}
