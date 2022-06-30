/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luc_chan <luc_chan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:25:32 by lchan             #+#    #+#             */
/*   Updated: 2022/06/30 15:32:11 by luc_chan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
static int lexer_add_nod(t_list **lexer_lst, char *start, char *end, unsigned index)
{
	t_lexer_token *new_content;

	new_content = ft_calloc(1, sizeof(t_lexer_token));
	if (!new_content)
		return (-1);
	new_content->index = index;
	new_content->start = start;
	new_content->end = end;
	new_content->length = end - start;
	ft_lstadd_back(lexer_lst, ft_lstnew(new_content));
	return (0);
}

t_list	*lexer_make(char *str)
{
	char			*start;
	char			*end;
	unsigned int	i;
	t_list			*lexer_head;

	start = str;
	end = str;
	i = 0;
	lexer_head = NULL;
	while (*start)
	{
		if (lexer_set_ptrs(&start, &end) == -1
		|| lexer_add_nod(&lexer_head, start, end, i++) == -1)
		{
			if (lexer_head)
				lexer_free(lexer_head);
			return (NULL);
		}
		start = end;
	}
	return (lexer_head);
}
*/
static int	lexer_add_nod (t_list **lexer_lst, t_lexer_token *tmp_nod)
{
	t_lexer_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lexer_token));
	if (!new_token)
		return (-1);
	new_token->index = tmp_nod->index;
	new_token->start = tmp_nod->start;
	new_token->end = tmp_nod->end;
	new_token->length = tmp_nod->end - tmp_nod->start;
	ft_lstadd_back(lexer_lst, ft_lstnew(new_token));
	return (0);
}


/**
 * @brief this funcion is
 *
 * @param str the user entry that is read by readline.
 * @return t_list* lexer. NULL is returned if an issue occurs.
 */
t_list	*lexer_make(char *str)
{
	t_list			*lexer_head;
	t_lexer_token	tmp_nod;

	lexer_head = NULL;
	tmp_nod.index = 0;
	tmp_nod.start = str;
	//tmp_nod.end = str;
	while (*(tmp_nod.start))
	{
		if (lexer_set_ptrs(&tmp_nod.start, &tmp_nod.end))
			lexer_error(&lexer_head, ERR_SOLO_QUOTE);//can add a secound round in case the quotes are not ended ?
		else if (lexer_type_checker(&lexer_head, &tmp_nod))
			lexer_error(&lexer_head, ERR_TYPE_CHECKER);//were the
		else if (lexer_add_nod(&lexer_head, &tmp_nod))
			lexer_error(&lexer_head, ERR_MALLOC_FAIL);// the only malloc spot is here, error has done by errno.
		tmp_nod.start = tmp_nod.end;
		tmp_nod.index++;
	}
	return(lexer_head);
}

