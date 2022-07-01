/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:18:19 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/01 13:21:24 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************
 * the goal of this function is to git the right type to the token.
 * 		it has to check if the operator is valid;
 * 			print error message syntax error near unexpected token `>>'
 * 		if the the end of readline is an operator
 * 			if its a redirection : has to ask for the redirection
 * 			else has to print syntax error near unexpected token `newline'.
 * theory :
 * 			after a redirection, we need a word.
 * 			after logical_operator we can have words or redirection but no logical_operator
 *
 *  */
int	lexer_type_checker(t_list **lexer_head, t_lexer_token *tmp_nod)
{
	printf("lexer_type_checker is suppose to give a type\n");
	return (0);
}
