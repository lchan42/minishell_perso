/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/01 16:02:57 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_free(t_list *lexer)
{
	t_list *tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
}

void	lexer_error(t_list **lexer, int error_id, t_lexer_token *tmp_nod)
{
	printf("an error has occured : %d\n", error_id);
	return ;
}
