/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/04 19:56:23 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_free(t_list *lexer)
{
	t_list *tmp;

	if (lexer)
		free (((t_lexer_token *)(lexer->content))->start);
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
	if (error_id)
		printf("ATTENTION ERROR NBR : %d\n", error_id);
	//lexer_free(*lexer);
	//*lexer = NULL;
	//exit(1) ;
}
