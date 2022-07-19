/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:35:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/19 16:24:28 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_set_heredoc(t_io *io, char *limit)
{
	char	buf[BUFFER_S];
	int		read_ret;

	read_ret = 1;
	if (io->here_buffer)
		__t_list_free(&(io->here_buffer));
	while (read_ret)
	{
		write(1, "heredoc> ", 14);
		read_ret = read(0, buf, BUFFER_S);
		buf[read_ret] = '\0';
		if (!(ft_strncmp(buf, limit, ft_strlen(limit))))
			break ;
		ft_lstadd_back(&(io->here_buffer), ft_lstnew(ft_strdup(buf)));
	}
	free(io->arg);
}
*/
void	save_io_arg(t_io *io)
{
	ft_lstadd_back(&(io->stock), ft_lstnew(io->arg));
}

void	save_here_d(t_io *io)
{
	char	*limit;
	char	buf[BUFFER_S];
	int		read_ret;

	limit = io->arg;
	read_ret = 1;
	if (io->here_buffer)
		__t_list_free(&(io->here_buffer));
	while (read_ret)
	{
		write(1, "> ", 2);
		read_ret = read(0, buf, BUFFER_S);
		buf[read_ret] = '\0';
		if (!(ft_strncmp(buf, limit, ft_strlen(limit))))
			break ;
		ft_lstadd_back(&(io->here_buffer), ft_lstnew(ft_strdup(buf)));
	}
	free(io->arg);
	io->arg = NULL;
}

void	__init_stock_mgmt(void(*stock_mgmt[7])(t_io *io))
{
	stock_mgmt[IN_D] =  &save_io_arg;
	stock_mgmt[HERE_D] = &save_here_d;
	stock_mgmt[OUT_D] = &save_io_arg;
	stock_mgmt[OUT_D_APP] = &save_io_arg;
}

t_list *__get_stock(t_io *io, int type)
{
	void	(*stock_mgmt[7])(t_io *io);
	__init_stock_mgmt(stock_mgmt);
	stock_mgmt[type](io);
	return (io->stock);
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
			return (OUT_D_APP);
		else
			return (OUT_D);
	}
}

static char *__get_arg(t_lexer_token *word, int type)
{
	char *arg;
	char *tmp;

	arg = ft_calloc(sizeof(char), (word->length + 2));
	if (!arg)
		return (NULL);
	tmp = word->start;
	if (type != HERE_D && word->length > 255)
		return (0); // add error return message "filename too long"
	while (tmp != word->end)
		*(arg++) = *(tmp++);
	*(arg)= '\0';
	if (type == OUT_D)
		*(arg + 1) = 'T';
	else if (type == OUT_D_APP)
		*(arg + 1) = 'A';
	return (arg - (word->length));
}

/*
void	__pars_errmsg(t_llist *redir, t_llist *word)
{
	int	type;

	type =
}
*/
static int	__pars_io_token(t_io *io, t_llist *redir, t_llist *word)
{
	if (word)
	{
		(io)->type = __get_redir_type((t_lexer_token *)(redir->content));
		// if ((io)->arg)
		//  	free((io)->arg);
		(io)->arg = __get_arg((t_lexer_token *)(word->content), (io)->type);
		(io)->fd = ((io)->type > 3);
		(io)->stock = __get_stock(io, (io)->type);
		return (1);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		return (-1); // add error message "unexpected token"
	}
}

static int __pars_io_pipe(t_io *i_o, t_lexer_token *token, int pipe_io)
{
	if (token->type == TYPE_LEXER_OPERATOR_LOGICAL)
	{
		i_o->type = pipe_io;
		i_o->fd = (i_o->type > 3);
		return (1);
	}
	//else if (token->type = TYPE_LEXER_SYNTAX_ERR)
		return (0);
}

int __init_io(t_io *in, t_io *out, t_llist *lexer)
{
	int res;

	//*in = ft_calloc(1, sizeof(t_io));
	//*out = ft_calloc(1, sizeof(t_io));
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
		else if (res == -1)
			return (-1);
		if (__pars_io_pipe(out, ((t_lexer_token *)lexer->content), PIPE_OUT))
			break ;
		lexer = lexer->next;
	}
	return (0);
}

//test >>1 <<2 | >>3 <<4 test5
//<infile1 <infile2 <infile3 <<1 >outfile1 >outfile2 > outfile3| >>3 <<2 test5
