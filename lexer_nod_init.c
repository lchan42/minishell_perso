/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_nod_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:25:32 by lchan             #+#    #+#             */
/*   Updated: 2022/06/24 17:47:58 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer_token	*lexer_nod_init(t_lexer_token *new_content)
{
	new_content = malloc(sizeof(t_lexer_token));
	if (!new_content)
		return (NULL);
	new_content->index = 0;
	new_content->type = 0;
	new_content->start = NULL;
	new_content->end = NULL;
	new_content->length = 0;
	return (new_content);
}

void lexer_lst_add_back(t_list **lexer_lst)
{
	t_lexer_token *new_content;

	new_content = ft_calloc(1, sizeof(t_lexer_token));
	//new_content = lexer_nod_init(new_content);
	ft_lstadd_back(lexer_lst, ft_lstnew(new_content));
}
