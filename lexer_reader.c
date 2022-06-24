/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:32:57 by lchan             #+#    #+#             */
/*   Updated: 2022/06/24 19:36:39 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reader_find_start(char *str, char *str_end)
{
	while (str != str_end && ft_strchr_b(" ", *str))
		str++;
	return (str);
}

static char *find_end_operator(char *end, char *str_end)
{
	while (end != str_end && ft_strchr_b(METACHAR, *end))
		end++;
	return (end);
}

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

static char *reader_find_end(char *end, char *str_end)
{
	if (ft_strchr_b(METACHAR, *end))
		end = find_end_operator(end, str_end);
	else
		end = find_end_word(end, str_end);
	return (end);
}

void	lexer_reader(char **start, char **end)
{
	char *str_end;

	str_end = *start + ft_strlen(*start);
	*start = reader_find_start(*start, str_end);
	*end = reader_find_end(*start, str_end);
}

