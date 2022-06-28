/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_nod_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:25:32 by lchan             #+#    #+#             */
/*   Updated: 2022/06/27 20:03:42 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
*/
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

static int lexer_lst_add_back(t_list **lexer_lst, char *start, char *end, unsigned index)
{
	t_lexer_token *new_content;

	new_content = ft_calloc(1, sizeof(t_lexer_token));
	if (!new_content)
		return (-1);
	//new_content = lexer_nod_init(new_content);
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
		||lexer_lst_add_back(&lexer_head, start, end, i++) == -1)
		{
			if (lexer_head)
				lexer_free(lexer_head);
			return (NULL);
		}
		start = end;
	}
	return (lexer_head);
}
