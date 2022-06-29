/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luc_chan <luc_chan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:16 by luc_chan          #+#    #+#             */
/*   Updated: 2022/06/29 17:22:12 by luc_chan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**********
 * error case:
 * multiple operator node are following each other
 * combinaison of meta char is invalid
 * lexer is ending by a metachar
 *
 *
*/
static int  is_word_or_operator(char *start, int len)
{

}

int lexer_analyser(t_list *lexer)
{
	int ret_type;

	while (lexer)
	{
		ret_type = lexer_set_type(lexer);
		if (ret_type)
			return (((t_lexer_token *)(lexer->content))->index); //returning the nod index containing the error;
		lexer = lexer->next;
	}
}
