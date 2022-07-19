/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/19 16:25:50 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_free(t_llist **lexer)
{
	t_llist *tmp;

	if (*lexer)
		free (((t_lexer_token *)((*lexer)->content))->start);
	while (*lexer)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp->content);
		free(tmp);
	}
	*lexer = NULL;
}

void	t_llist_free(t_llist **lexer)
{
	t_llist *tmp;

	while (*lexer)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp->content);
		free(tmp);
	}
	*lexer = NULL;
}

void	lexer_data_free(t_lexer_data **lexer_data)
{
	if (*lexer_data)
	{
		if ((*lexer_data)->lexer)
			t_llist_free((&(*lexer_data)->lexer));
		if ((*lexer_data)->read_lst)
			t_llist_free((&(*lexer_data)->read_lst));
		free(*lexer_data);
		*lexer_data = NULL;
	}
}
