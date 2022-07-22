/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:26:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/22 20:05:34 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__lexer_end_pipe_check(t_llist **lexer)
{
	t_llist	*tmp;

	tmp = ft_llstlast(*lexer);
	if (!tmp || *lexer == tmp)
		return ;
	if (((t_lexer_token *)tmp->content)->type == TYPE_LEXER_OPERATOR_LOGICAL)
	{
		printf("minishell: syntax error near unexpected token '%.*s'\n",
			(int)(((t_lexer_token *)tmp->content)->length),
			((t_lexer_token *)tmp->content)->start);
		lexer_free(lexer);
	}
}

t_llist	*lexer(char *usr_input)
{
	t_llist	*lexer;

	lexer = NULL;
	lexer_make(&lexer, usr_input);
	if (lexer)
		__lexer_end_pipe_check(&lexer);
	return (lexer);
}
