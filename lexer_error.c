/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/13 14:15:12 by lchan            ###   ########.fr       */
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

void	lexer_data_free(t_lexer_data *l_data)
{
	if (l_data)
	{
		if (l_data->lexer)
			t_llist_free(&l_data->lexer);
		if (l_data->read_lst)
			t_llist_free(&l_data->read_lst);
		if (l_data)
			free(l_data);
	}
}

// int	lexer_error(t_lexer_data *l_data, int error_id, t_lexer_token *tmp_nod)
// {
// 	if (!error_id)
// 		return (0);
// 	else if (error_id == ERR_END_PIPE)
// 		lexer_loop(l_data);
// 	else
// 	{
// 		if (error_id == ERR_SOLO_QUOTE)
// 			printf("minishell: our project does not accept unclosed quotation\n");
// 		else if (error_id == ERR_SYNTAX)
// 			printf("minishell: syntax error near unexpected token '%.*s'\n",
// 			(int)(tmp_nod->length) , tmp_nod->start);
// 		else if (error_id == ERR_SYNTAX_NL)
// 			printf("minishell: syntax error near unexpected token `newline'\n");
// 	}
// 	return (error_id);
// }
