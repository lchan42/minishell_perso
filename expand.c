/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:12:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/26 11:28:38 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__is_expandable(char *str)
{
	static char	quote_flag1 = 0;

	if (*str == '\0')
	{
		quote_flag1 = 0;
		return (NULL);
	}
	if (quote_flag1 == 0 || quote_flag1 == '\'')
		quote_flag1 ^= (*str == '\'') * '\'';
	if (quote_flag1 == 0 || quote_flag1 == '\"')
		quote_flag1 ^= (*str == '\"') * '\"';
	if (*str == '$'
		&& (ft_isalnum((*(str + 1))) ||  ft_strchr_b("_\"\'", *(str + 1)))
		&& *(str + 1) && quote_flag1 != '\'')
		{
			if (!(*(str + 1) == quote_flag1))
			{
				if (!(quote_flag1 == '\"' && *(str + 1) == '\''))
					return (str);
			}
		}
	return (__is_expandable(str + 1));
}

//test'$USER' $"USER" $'USER' "$USER" $ "'$USER'" "$'USER'" $$$USER $"$'USER" "$$$USER" '$$$USER' $"$USER'''" --> input
//test$USER USER USER slahlou $ 'slahlou' $'USER' 474255slahlou $'USER 474255slahlou $$$USER slahlou''' --> bash output
//
// erreur sur :
// $'USER'
// "'$USER'"$;
// "$'USER'"

// ""$"U'S'ER'$',,,$USER$$'U'SR" --> input
// U'S'ER'$',,,slahlou474255'U'SR  --> bash output
// """U'S'ER'$',,,slahlou$$'U'SR" --> minishell output //seems OK

// "$'USER', U S E'$'R :$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$" --> input
// $'USER', U S E'$'R :$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$ --> bash output
// "$'USER', U S E'$'R :$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$" --> minishell output //seems OK

// $"$'USER" -->input
// $'USER -->bash output
// $'USER -->  minishell output //seems OK

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

char	*__add_exp_to_str(char *str, char **start, char *end, char *expand)
{
	int	len_str;
	int	full_len;
	char	*tmp;

	len_str = ft_strlen_p(str);
	full_len = (len_str - 1) - (end - *start) + ft_strlen_p(expand);
	tmp = ft_calloc(sizeof(char), full_len + 1);
	if (!tmp)
		return (NULL);
	while(str != *start - 1)
		*(tmp++) = *(str++);
	str = end;
	while (expand && *expand)
		*(tmp++) = *(expand++);
	*start = tmp;
	while (*str)
		*(tmp++) = *(str++);
	free (str - len_str);
	return (tmp - full_len);
}

char	*__is_hd_expandable(char *str)
{
	while (*str)
	{
		if (*str == '$' && (ft_isalnum((*(str + 1))) ||  ft_strchr_b("_", *(str + 1))))
			return (str);
		str++;
	}
	return (NULL);
}

char	*__expand_string(char *str, char **env, int opt)
{
	char	*start;
	char	*end;
	char	*expand;

	start = str;
	while (start)
	{
		if (!opt)
			start = __is_expandable(start);
		else
			start = __is_hd_expandable(start);
		if (start)
		{
			//printf("%s is expandable\n", start);
			end = ++start;
			if (!ft_isdigit(*end))
				while (*end && (ft_isalnum(*end) || *end == '_'))
					end++;
			else
				end++;
			expand = __get_expand(start, end - start, env);
			//printf("expand = %s\n", expand);
			str = __add_exp_to_str(str, &start, end, expand);
			//str = start;
		}
	}
	return (str);
}

void	__expand_t_list(t_list *lst, char **env, int opt)
{
	if (lst)
	{
		if (opt && !ft_strncmp((char *)lst->content, HD_EXP, ft_strlen_p(HD_EXP)))
			lst = lst->next;
		else if (opt)
			return ;
		while (lst)
		{
			lst->content = __expand_string((char *)lst->content, env, opt);
			lst = lst->next;
		}
	}
}

t_splcmd	*__expand(t_splcmd *parser, char **env)
{
	if (parser)
	{
		__expand_t_list(parser->in.stock, env, 0);
		__expand_t_list(parser->in.here_buffer, env, 1);
		__expand_t_list(parser->out.stock, env, 0);
		__expand_t_list(parser->cmd.cmd_lst, env, 0);
	}
	return (parser);
}
