/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:12:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/25 13:49:24 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__is_expandable(char *str)
{
	static char quote_flag1 = 0;

	if (*str == '\0')
		return (NULL);
	if (quote_flag1 == 0 || quote_flag1 == '\'')
		quote_flag1 ^= (*str == '\'') * '\'';
	if (quote_flag1 == 0 || quote_flag1 == '\"')
		quote_flag1 ^= (*str == '\"') * '\"';
	if (*str == '$' && *(str + 1) != ' ' && *(str + 1) && quote_flag1 != '\'')
		return (str);
	return (__is_expandable(str + 1));
}
//ft_isalnum((*(str + 1)) || *(str + 1) == '_')
char	*__get_expand(char *start, int len, char **env)
{
	while (*env)
	{
		if (*(*env + len) == '=' && !ft_strncmp(start, *env, len))
			return (*env + len + 1);
		env++;
	}
	return (*env);
}

char	*__expand_string(char *str, char **env)
{
	char	*start;
	char	*end;
	char	*expand;

	start = str;
	while (start)
	{
		start = __is_expandable(start);
		if (start)
		{
			end = ++start;
			while (*end && (ft_isalnum(*end) || *end == '_'))
				end++;
			expand = __get_expand(start, end - start, env);
			printf("expand = %s\n", expand);
		}
	}
	return (NULL);
}

void	__expand_t_list(t_list *lst, char **env)
{
	while (lst)
	{
		lst->content = __expand_string((char *)lst->content, env);
		lst = lst->next;
	}
}

t_splcmd	*__expand(t_splcmd *parser, char **env)
{
	if (parser)
	{
		__expand_t_list(parser->in.stock, env);
		__expand_t_list(parser->in.here_buffer, env);
		__expand_t_list(parser->out.stock, env);
		__expand_t_list(parser->cmd.cmd_lst, env);
	}
	return (NULL);
}
