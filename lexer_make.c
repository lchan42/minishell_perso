/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:25:32 by lchan             #+#    #+#             */
/*   Updated: 2022/07/04 20:58:10 by lchan            ###   ########.fr       */
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
// static int	lexer_add_nod (t_list **lexer_lst, t_lexer_token *tmp_nod)
// {
// 	t_lexer_token	*new_token;

// 	new_token = ft_calloc(1, sizeof(t_lexer_token));
// 	if (!new_token)
// 		return (-1);
// 	new_token->index = tmp_nod->index;
// 	new_token->start = tmp_nod->start;
// 	new_token->end = tmp_nod->end;
// 	new_token->length = tmp_nod->end - tmp_nod->start;
// 	if (ft_strchr_b(METACHAR, *(new_token->start)))
// 	{
// 		if (ft_strchr_b(LOG_META, *(new_token->start)))
// 			new_token->type = TYPE_LEXER_OPERATOR_LOGICAL;
// 		else
// 			new_token->type = TYPE_LEXER_OPERATOR_REDIRECT;
// 	}
// 	else
// 		new_token->type = TYPE_LEXER_WORD;
// 	ft_lstadd_back(lexer_lst, ft_lstnew(new_token));
// 	return (0);
// }

// /**
//  * @brief this funcion is
//  *
//  * @param str the user entry that is read by readline.
//  * @return t_list* lexer. NULL is returned if an issue occurs.
//  */
// t_list	*lexer_make(char *str)
// {
// 	t_list			*lexer_head;
// 	t_lexer_token	tmp_nod;

// 	lexer_head = NULL;
// 	tmp_nod.index = 0;
// 	tmp_nod.start = str;
// 	//tmp_nod.end = str; it seems that I dont need to set it. kept in case error mgmt needs it.
// 	while (*(tmp_nod.start))
// 	{
// 		if (lexer_set_ptrs(&tmp_nod.start, &tmp_nod.end))
// 			lexer_error(&lexer_head, ERR_SOLO_QUOTE);//can add a secound round in case the quotes are not ended ?
// 		else if (lexer_type_checker(&lexer_head, &tmp_nod))
// 			lexer_error(&lexer_head, ERR_TYPE_CHECKER);//were the
// 		else if (lexer_add_nod(&lexer_head, &tmp_nod))
// 			lexer_error(&lexer_head, ERR_MALLOC_FAIL);// the only malloc spot is here, error has done by errno.
// 		tmp_nod.start = tmp_nod.end;
// 		tmp_nod.index++;
// 	}
// 	return(lexer_head);
// }


static t_lexer_token *lexer_add_nod (t_list **lexer_lst, t_lexer_token *tmp_nod)
{
	t_lexer_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lexer_token));
	if (!new_token)
		return (NULL);
	new_token->index = tmp_nod->index;
	new_token->start = tmp_nod->start;
	new_token->end = tmp_nod->end;
	new_token->length = tmp_nod->end - tmp_nod->start;
	new_token->type = tmp_nod->type;
	ft_lstadd_back(lexer_lst, ft_lstnew(new_token));
	return (new_token);
}

static void lexer_give_type(t_lexer_token *tmp_nod)
{
	if (ft_strchr_b(METACHAR, *(tmp_nod->start)))
	{
		if (ft_strchr_b(LOG_META, *(tmp_nod->start)))
			tmp_nod->type = TYPE_LEXER_OPERATOR_LOGICAL;
		else
			tmp_nod->type = TYPE_LEXER_OPERATOR_REDIRECT;
	}
		else
			tmp_nod->type = TYPE_LEXER_WORD;
}

/********************
 * Syntaxe error list
 *  * End
 * 		| --> reloop
 * 		> --> syntax error
 * Start
 * 		by a TYPE_LEXER_OPERATOR_LOGICAL
 * middle
 * 		| followed by another |
 * 		> followed by not a word
 * **/
static int	lexer_syntax_checker(t_lexer_token *last_nod, t_lexer_token *tmp_nod)
{
	if (!tmp_nod)
	{
		if (last_nod->type == TYPE_LEXER_OPERATOR_LOGICAL)
			return (ERR_SYNTAX);
		else if (last_nod->type == TYPE_LEXER_OPERATOR_REDIRECT)
			return (ERR_SYNTAX);
	}
	else if (tmp_nod->type != TYPE_LEXER_WORD)
	{
		if (tmp_nod->index == 0 && tmp_nod->type == TYPE_LEXER_OPERATOR_LOGICAL)
			return (ERR_SYNTAX);
		else if (last_nod && last_nod->type != TYPE_LEXER_WORD)
		{
			if ((last_nod->type == TYPE_LEXER_OPERATOR_LOGICAL
			&& last_nod->type == tmp_nod->type)
			|| (last_nod->type == TYPE_LEXER_OPERATOR_REDIRECT
			&& tmp_nod->type != TYPE_LEXER_WORD))
				return (ERR_SYNTAX);
		}
	}
	return (0);
}

static void lexer_make_init(t_list **lexer_head, t_lexer_token **last_nod,
							t_lexer_token *tmp_nod, char *str)
{
	*lexer_head = NULL;
	*last_nod = NULL;
	tmp_nod->index = 0;
	tmp_nod->start = str;
	tmp_nod->end = str;
}

/**
 * @brief this funcion is
 *
 * @param str the user entry that is read by readline.
 * @return t_list* lexer. NULL is returned if an issue occurs.
 */
/***************
 * tmp_nod is used as a pattern to build malloc nods.
 * We compare the last malloc nod with tmp_nod. If syntaxe is ok we malloc again.
 * in order:
 * 		on tmp_nod : set the ptrs + controle of solo quote case
 *		tmp_nod.start == tmp_nod.end means user ended the str with a space  --> break ;
 *		set the type of the token on tmp_nod
 *		check for syntaxe error error

 * **/
t_list	*lexer_make(char *str)
{
	t_list			*lexer_head;
	t_lexer_token	*last_nod;
	t_lexer_token	tmp_nod;

	lexer_make_init(&lexer_head, &last_nod, &tmp_nod, str);
	while (*(tmp_nod.start))
	{
		if (lexer_set_ptrs(&tmp_nod.start, &tmp_nod.end))
			lexer_error(&lexer_head, ERR_SOLO_QUOTE, &tmp_nod);
		if (tmp_nod.start == tmp_nod.end)
			break ;
		lexer_give_type(&tmp_nod);
		lexer_error(&lexer_head, lexer_syntax_checker(last_nod, &tmp_nod), &tmp_nod);
		last_nod = lexer_add_nod(&lexer_head, &tmp_nod);
		if (!last_nod)
			lexer_error(&lexer_head, ERR_MALLOC_FAIL, &tmp_nod); // the only malloc spot is here, error has done by errno.
		tmp_nod.start = tmp_nod.end;
		tmp_nod.index++;
	}
	if (lexer_head);
		lexer_error(&lexer_head, lexer_syntax_checker(last_nod, NULL), last_nod);
	return(lexer_head);
}
