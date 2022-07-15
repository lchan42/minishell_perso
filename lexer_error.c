/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/15 12:27:02 by lchan            ###   ########.fr       */
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

void	lexer_data_free(t_lexer_data **l_data)
{
	if (*l_data)
	{
		if ((*l_data)->lexer)
			t_llist_free((&(*l_data)->lexer));
		if ((*l_data)->read_lst)
			t_llist_free((&(*l_data)->read_lst));
		free(*l_data);
		*l_data = NULL;
	}
}
