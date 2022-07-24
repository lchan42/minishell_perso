/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:12:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/23 18:47:12 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__is_expandable(char *str)
{
	int	quote_flag;

	quote_flag = 0;
	while (str)
	{
		if (!quote_flag && ft_strchr(("\"\'"), *str))
			quote_flag = *str;
		else if (quote_flag && *str == quote_flag)
			quote_flag = 0;
		if ((quote_flag == '\"' || quote_flag == 0) && *str = '$')
			return (str);
		str++;
	}
	return (NULL);
}

void	__expand_t_list(t_list *lst)
{
	char *expand_start;

	while (lst)
	{
		expand_start = (char *)lst->content;
		expand_start = __is_expandable(expand_start);
		lst = lst->next;
	}
}

t_splcmd	*__expand(t_splcmd *parser, char **env)
{
	__expand_t_list(parser->in.stock);
	__expand_t_list(parser->in.here_buffer);
	__expand_t_list(parser->out.stock);
	__expand_t_list(parser->cmd.cmd_lst);
}
