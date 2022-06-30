/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_ptrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luc_chan <luc_chan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:32:57 by lchan             #+#    #+#             */
/*   Updated: 2022/06/29 20:32:59 by luc_chan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************************************
 * skip all spaces and return the position of the first non space character
 */
static char	*set_ptrs_start(char *str, char *str_end)
{
	while (str != str_end && ft_strchr_b(" ", *str))
		str++;
	return (str);
}

/************************
 * find end case operator
 * 		skip bits while is an operator
 */
static char *find_end_operator(char *start, char *str_end)
{
	char *end;

	end = start;
	while (end != str_end && ft_strchr_b(METACHAR, *end)) //might have 
		end++;
	return (end);
}

/***************************************************************************
 * find end case word
 * 		skip bits until a metacharacter ("|&()<> ") is encountered
 * if a quote is encountered, skip bits until end of quote is encountered
 * 		end of quote do not necessarly imply end of token
 * 		returns NULL if no end of quote is encountered
 */
static char *find_end_word(char *end, char *str_end)
{
	int		quote_flag;

	quote_flag = 0;
	while (end != str_end &&
		ft_strchr_b(METACHAR, *end) == 0 && ft_strchr_b(" ", *end) == 0)
	{
		if (*end == '"')
			quote_flag = '"';
		else if (*end == '\'')
			quote_flag = '\'';
		while (quote_flag && end++)
		{
			if (*end == quote_flag)
				quote_flag = 0;
			else if (*end == '\0')
				return (NULL);
		}
		end++;
	}
	return (end);
}

/***************************************************************************
 * return the end of token according to the start address
 */
static char *set_ptrs_end(char *start, char *str_end)
{
	char *end;

	if (ft_strchr_b(METACHAR, *start))
		end = find_end_operator(start, str_end);
	else
		end = find_end_word(start, str_end);
	return (end);
}

/**
 * @brief set its parameters so they delimit the start and the end of a token. returns -1 in case of problem
 *
 * @param start start of the token
 * @param end end of the token
 */
int	lexer_set_ptrs(char **start, char **end)
{
	char *str_end;

	str_end = *start + ft_strlen(*start);
	*start = set_ptrs_start(*start, str_end);
	*end = set_ptrs_end(*start, str_end);
	if (*end == NULL)
		return (-1);
	return (0);

}
