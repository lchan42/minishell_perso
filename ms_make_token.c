/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:46:51 by lchan             #+#    #+#             */
/*   Updated: 2022/06/15 18:27:44 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*__word_jump(char *str, const char delim)
// {
// 	int	flag;

// 	flag = 0;
// 	while (*str && *str != delim)
// 	{
// 		if (*str == '\'' || *str == '"')
// 			flag = 1;
// 		while (flag)
// 		{
// 			str++;
// 			if ( *str == '\0' || *str == '\'' || *str == '"')
// 				flag = 0;
// 		}
// 		str++;
// 	}
// 	return (str);
// }

// static int	__count_word(char *str, const char delim)
// {
// 	int	flag;
// 	int	word_cnt;

// 	flag = 1;
// 	word_cnt = 0;
// 	while (str && *str)
// 	{
// 		if (flag && *str != delim)
// 		{
// 			flag = 0;
// 			word_cnt++;
// 			while (*str && *str != delim)
// 				str++;
// 		}
// 		else if (!flag)
// 			flag = 1;
// 		while (str && *str == delim)
// 			str++;
// 	}
// 	return(word_cnt);
// }

// void	__make_token (char *str, const char delim)
// {
// 	int	str_len;
// 	int	word_cnt;

// 	str_len = strlen(str);///////////
// 	word_cnt = __count_word(str, delim);
// 	while (*str)
// 	{
// 		str = __word_jump(str, delim);
// 		printf("str = %s\n", str);
// 		str++;
// 	}
// 	printf("word count = %d\n", word_cnt);
// }


// static int	ft_strlen(char *str)
// {
// 	int cnt;

// 	cnt = 0;
// 	while (*str++)
// 		cnt++;
// 	return (cnt);
// }

// static char	*__word_jump(char *str, const char delim)
// {
// 	int	flag;

// 	flag = 0;
// 	while (*str && *str != delim)
// 	{
// 		if (*str == '\'' || *str == '"')
// 			flag = 1;
// 		while (flag)
// 		{
// 			str++;
// 			if ( *str == '\0' || *str == '\'' || *str == '"')
// 				flag = 0;
// 		}
// 		str++;
// 	}
// 	return (str);
// }

// static int	__put_null_byte(char *str, const char delim, char *str_end)
// {
// 	int	cnt;

// 	cnt = 0;
// 	while (str != str_end)
// 	{
// 		str = __word_jump(str, delim);
// 		if ((*str == delim || *str == '\0') && ++cnt)
// 			*str = '\0';
// 		if (str != str_end)
// 			str++;
// 	}
// 	return(cnt);
// }
// /*********************************
//  * put null byte to str according to the token.
//  * *******************************/

// void	__make_token(char *str, const char delim)
// {
// 	int len;

// 	len = ft_strlen(str);
// 	printf("len = %d\n", len);
// 	printf("put_null_byte = %d\n", __put_null_byte(str, delim, str + len));
// 	while (len--)
// 	{
// 		write (1, str, 1);
// 		if (*str == '\0')
// 			write(1, "\n", 1);
// 		str++;
// 	}
// 	//__put_ptr(str, delim, str + len);
// }

/************************************************************************************************************************************************/
/*********************** FROM LIBFT *****************************/
static int	ft_strlen(char *str)
{
	int cnt;

	cnt = 0;
	while (*str++)
		cnt++;
	return (cnt);
}

int	ft_strchr_boolean(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (1);
		i++;
	}
	return (0);
}
/****************************************************************/

static int __str_word_jump(char **str, const char *delim)
{
	int		quote_flag;
	char	*tmp;

	quote_flag = 0;
	tmp = *str;
	while (ft_strchr_boolean(delim, *tmp))
		tmp++;
	while (*tmp && ft_strchr_boolean(delim, *tmp) == 0)
	{
		if (*tmp == '"')
			quote_flag = '"';
		else if (*tmp == '\'')
			quote_flag = '\'';
		while (quote_flag && tmp++)
		{
			if (*tmp == quote_flag)
				quote_flag = 0;
			else if (*tmp == '\0')
				return (-1);
		}
		tmp++;
	}
	*str = tmp;
	return (1);
}
/* ***********************************************************************
 * Definition : a word has at its R and L side either nothing or a delim
 * In order :
 * 		first while: tmp++ until it reaches a non delim
 * 		second while: tmp++ until it reaches a delim
 * 			third while:	tmp++ untel we reach a quote
 * 							send -1 if no quote
 * **********************************************************************/

static int	__set_null_bytes(char *str, const char *delim, char *str_end)
{
	int	cnt;

	cnt = 0;
	while (str != str_end)
	{
		if(__str_word_jump(&str, delim) == -1)
			return (-1);
		if (ft_strchr_boolean(delim, *str) && ++cnt)
			*str = '\0';
		else if (str == str_end && !ft_strchr_boolean(delim, *(str - 1)))
				cnt++;
		if (str != str_end)
			str++;
		else
			break ;
	}
	return (cnt);
}
/* ****************************************************************
 * put one null byte at the end of each words.
 * return the number of null byte that the str contains in the end
 * ****************************************************************/

static char	*__save_ptr(char *str, const char *delim, char *str_end)
{
	while ((ft_strchr_boolean(delim, *str) || *str == '\0') && str != str_end)
		str++;
	if (*str)
		return (str);
	else
		return (NULL);
}

char	**__make_token(char *str, const char *delim)
{
	char	*str_end;
	int		cnt;
	int		i;
	char	**token_tab;

	str_end = str + ft_strlen(str);
	cnt = __set_null_bytes(str, delim, str_end);
	if (cnt == -1)
		return (NULL);
	token_tab = (char **) malloc(sizeof(char *) * (cnt + 1));
	if (token_tab)
	{
		i = -1;
		token_tab[cnt] == NULL;
		while (++i < cnt)
			token_tab[i] = __save_ptr(str, delim, str_end);
	}
	return (token_tab);
}
/* ****************************************************************
 * cnt = -1 means that the entry is incorrect (single ' or ");
 * ****************************************************************/
