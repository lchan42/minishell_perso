/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/06 11:43:12 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	lexer_free(t_list *lexer)
// {
// 	t_list *tmp;

// 	if (lexer)
// 		free (((t_lexer_token *)(lexer->content))->start);
// 	while (lexer)
// 	{
// 		tmp = lexer;
// 		lexer = lexer->next;
// 		free(tmp->content);
// 		free(tmp);
// 	}
// }
void	lexer_free(t_list **lexer)
{
	t_list *tmp;

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

void	t_list_free(t_list **lexer)
{
	t_list *tmp;

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
	t_list_free(&l_data->lexer);
	t_list_free(&l_data->read_lst);
}

int	lexer_error(t_lexer_data *l_data, int error_id, t_lexer_token *tmp_nod)
{
	//char *str;

	if (!error_id)
		return (0);
	else if (error_id == ERR_END_PIPE)
	{
		//printf("str = %s\n", str);
		printf("reloop function");
		lexer_loop(l_data);
	}
	else
	{
		printf("ATTENTION ERROR NBR : %d\n", error_id);
		if (error_id == ERR_SOLO_QUOTE)
			printf("minishell: our project does not accept unclosed quotation\n");
		else if (error_id == ERR_SYNTAX)
			printf("minishell: syntax error near unexpected token '%.*s'\n",
			(int)tmp_nod->length, tmp_nod->start);
		else if (error_id == ERR_SYNTAX_NL)
			printf("minishell: syntax error near unexpected token `newline'\n");
		lexer_data_free(l_data); ///// HIS LINE IS TEMPORARY HERE free should be done after the history ?
	}
	//HAVE TO ADD HISTORIC FUNCTION HERE
	return (error_id);
}
