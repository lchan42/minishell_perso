/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:25:32 by lchan             #+#    #+#             */
/*   Updated: 2022/07/12 20:16:59 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// static t_lexer_token *lexer_add_nod (t_list **lexer_lst, t_lexer_token *tmp_nod)
// {
// 	t_lexer_token	*new_token;

// 	new_token = ft_calloc(1, sizeof(t_lexer_token));
// 	if (!new_token)
// 		return (NULL);
// 	new_token->index = tmp_nod->index;
// 	new_token->start = tmp_nod->start;
// 	new_token->end = tmp_nod->end;
// 	new_token->length = tmp_nod->length;
// 	new_token->type = tmp_nod->type;
// 	ft_lstadd_back(lexer_lst, ft_lstnew(new_token));
// 	return (new_token);
// }

// /*********************
//  * give the right start and end and set the type.
//  * set the length;
//  * return : non 0 value if problem, 0 if ok.
//  */
// static int lexer_set_tmp_nod(t_lexer_token *tmp_nod)
// {
// 	if (lexer_set_ptrs(&tmp_nod->start, &tmp_nod->end))
// 		return (ERR_SOLO_QUOTE);
// 	tmp_nod->length = tmp_nod->end - tmp_nod->start;
// 	if (ft_strchr_b(METACHAR, *(tmp_nod->start)))
// 	{
// 		if (ft_strchr_b(LOG_META, *(tmp_nod->start)))
// 			tmp_nod->type = TYPE_LEXER_OPERATOR_LOGICAL;
// 		else
// 			tmp_nod->type = TYPE_LEXER_OPERATOR_REDIRECT;
// 	}
// 	else
// 		tmp_nod->type = TYPE_LEXER_WORD;
// 	return (0);
// }

// /********************
//  * Syntaxe error. Doing different things according to the nod position.
//  * End (final nod)
//  * 		| --> reloop
//  * 		> --> syntax error
//  * Start (first nod)
//  * 		TYPE_LEXER_OPERATOR_LOGICAL -->syntax error
//  * middle (intermediate nod)
//  * 		| followed by another |
//  * 		> followed by not a word
//  * **/
// static int	lexer_syntax_checker(t_lexer_token *last_nod, t_lexer_token *tmp_nod)
// {
// 	if (!tmp_nod)
// 	{
// 		if (last_nod->type == TYPE_LEXER_OPERATOR_LOGICAL)
// 			return (ERR_END_PIPE);
// 		else if (last_nod->type == TYPE_LEXER_OPERATOR_REDIRECT)
// 			return (ERR_SYNTAX_NL);
// 	}
// 	else if (tmp_nod->type != TYPE_LEXER_WORD)
// 	{
// 		if (tmp_nod->index == 0 && tmp_nod->type == TYPE_LEXER_OPERATOR_LOGICAL)
// 			return (ERR_SYNTAX);
// 		else if (last_nod && last_nod->type != TYPE_LEXER_WORD)
// 		{
// 			if ((last_nod->type == TYPE_LEXER_OPERATOR_LOGICAL
// 			&& last_nod->type == tmp_nod->type)
// 			|| (last_nod->type == TYPE_LEXER_OPERATOR_REDIRECT
// 			&& tmp_nod->type != TYPE_LEXER_WORD))
// 				return (ERR_SYNTAX);
// 		}
// 	}
// 	return (0);
// }

// /**
//  * @brief this funcion modifies l_data->lexer according to str. if str is valide it will creats token. if not, params remain unchanged
//  *
//  * @param l_data contains t_list->lexer and t_list->read_lst
//  * @param str return of readline (user's entry).
//  */
// /************************* additional informations *****************************************
//  * tmp_nod is used as a pattern to build malloc nods.
//  * We compare the last malloc nod with tmp_nod. If syntax is ok we malloc.
//  * in the while loop:
//  * 		tmp_nod : set the ptrs + controle of solo quote case
//  *		tmp_nod.start == tmp_nod.end means used ended the str with spaces --> break;
//  *		set the type of the token on tmp_nod
//  *		check for syntaxe errors
//  * after the while loop we have 2 cases:
//  * 		last_nod exist == str has none space char --> can analyse the syntax
//  * 		last_nod do not exit but we have a lexer address == user entered only space or nothing during reloop--> ask new entry
//  *	if user entered only space, l_data and str will remain unchanged
//  * **/
// void	lexer_make(t_lexer_data *l_data, char *str)
// {
// 	t_lexer_token	*last_nod;
// 	t_lexer_token	tmp_nod;

// 	last_nod = NULL;
// 	tmp_nod.index = 0;
// 	tmp_nod.start = str;
// 	tmp_nod.end = str;
// 	while (*(tmp_nod.start))
// 	{
// 		if (lexer_error(l_data, lexer_set_tmp_nod(&tmp_nod), &tmp_nod)
// 		|| tmp_nod.start == tmp_nod.end)
// 			break ;
// 		if (lexer_error(l_data, lexer_syntax_checker(last_nod, &tmp_nod), &tmp_nod))
// 			break ;
// 		last_nod = lexer_add_nod(&l_data->lexer, &tmp_nod);
// 		if (!last_nod)
// 			lexer_error(l_data, ERR_MALLOC_FAIL, &tmp_nod); // the only malloc spot is here, error has done by errno.
// 		tmp_nod.start = tmp_nod.end;
// 		tmp_nod.index++;
// 	}
// 	if (l_data->lexer && last_nod)
// 		lexer_error(l_data, lexer_syntax_checker(last_nod, NULL), last_nod);
// 	else if (l_data->lexer)
// 		lexer_loop(l_data);
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
	new_token->length = tmp_nod->length;
	new_token->type = tmp_nod->type;
	ft_lstadd_back(lexer_lst, ft_lstnew(new_token));
	return (new_token);
}

/*********************
 * give the right start and end and set the type.
 * set the length;
 * return : non 0 value if problem, 0 if ok.
 */
static int lexer_set_tmp_nod(t_lexer_token *tmp_nod)
{
	if (lexer_set_ptrs(&tmp_nod->start, &tmp_nod->end))
		return (ERR_SOLO_QUOTE);
	tmp_nod->length = tmp_nod->end - tmp_nod->start;
	if (ft_strchr_b(METACHAR, *(tmp_nod->start)))
	{
		if (ft_strchr_b(LOG_META, *(tmp_nod->start)))
			tmp_nod->type = TYPE_LEXER_OPERATOR_LOGICAL;
		else
			tmp_nod->type = TYPE_LEXER_OPERATOR_REDIRECT;
	}
	else
		tmp_nod->type = TYPE_LEXER_WORD;
	return (0);
}

/********************
 * Syntaxe error. Doing different things according to the nod position.
 * End (final nod)
 * 		| --> reloop
 * 		> --> syntax error
 * Start (first nod)
 * 		TYPE_LEXER_OPERATOR_LOGICAL -->syntax error
 * middle (intermediate nod)
 * 		| followed by another |
 * 		> followed by not a word
 * **/
static int	lexer_syntax_checker(t_lexer_token *last_nod, t_lexer_token *tmp_nod)
{
	if (!tmp_nod)
	{
		if (last_nod->type == TYPE_LEXER_OPERATOR_LOGICAL)
			return (ERR_END_PIPE);
		else if (last_nod->type == TYPE_LEXER_OPERATOR_REDIRECT)
			return (ERR_SYNTAX_NL);
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

/**
 * @brief this funcion modifies l_data->lexer according to str. if str is valide it will creats token. if not, params remain unchanged
 *
 * @param l_data contains t_list->lexer and t_list->read_lst
 * @param str return of readline (user's entry).
 */
/************************* additional informations *****************************************
 * tmp_nod is used as a pattern to build malloc nods.
 * We compare the last malloc nod with tmp_nod. If syntax is ok we malloc.
 * in the while loop:
 * 		tmp_nod : set the ptrs + controle of solo quote case
 *		tmp_nod.start == tmp_nod.end means used ended the str with spaces --> break;
 *		set the type of the token on tmp_nod
 *		check for syntaxe errors
 * after the while loop we have 2 cases:
 * 		last_nod exist == str has none space char --> can analyse the syntax
 * 		last_nod do not exit but we have a lexer address == user entered only space or nothing during reloop--> ask new entry
 *	if user entered only space, l_data and str will remain unchanged
 * **/
void	lexer_make(t_lexer_data *l_data, char *str)
{
	t_lexer_token	*last_nod;
	t_lexer_token	tmp_nod;

	last_nod = NULL;
	tmp_nod.index = 0;
	tmp_nod.start = str;
	tmp_nod.end = str;
	while (*(tmp_nod.start))
	{
		if (lexer_error(l_data, lexer_set_tmp_nod(&tmp_nod), &tmp_nod)
		|| tmp_nod.start == tmp_nod.end)
			return ;
		if (lexer_error(l_data, lexer_syntax_checker(last_nod, &tmp_nod), &tmp_nod))
			return ;
		last_nod = lexer_add_nod(&l_data->lexer, &tmp_nod);
		if (!last_nod)
			lexer_error(l_data, ERR_MALLOC_FAIL, &tmp_nod); // the only malloc spot is here, error has done by errno.
		tmp_nod.start = tmp_nod.end;
		tmp_nod.index++;
	}
	//if (l_data->lexer && last_nod)								//syntax error 'nexline' has to be done later
	//	lexer_error(l_data, lexer_syntax_checker(last_nod, NULL), last_nod);
	//else if (l_data->lexer)
	//	lexer_loop(l_data);
}

