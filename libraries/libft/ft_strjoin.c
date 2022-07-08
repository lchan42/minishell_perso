/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:11:28 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 15:03:05 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	index;

	index = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (s1 && *s1 != '\0')
	{
		joined[index] = *s1;
		s1++;
		index++;
	}
	while (s2 && *s2 != '\0')
	{
		joined[index] = *s2;
		s2++;
		index++;
	}
	joined[index] = '\0';
	return (joined);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_p(s1);
	len_s2 = ft_strlen_p(s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		while (len_s1)
		*(--joined) = s1[--len_s1];
	}
	return (joined);
}

/**
 * @brief	modified strjoin. Uses ft_strlen_p.
 *
 * @param s1
 * @param s2
 * @return pointer toward malloc of joined s1  and s2.
 * difference If !s1 || !s2 act as ft_strdup. Also if !s1 && !s2, returns "\0"
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	len_s1 = ft_strlen_p(s1);
	len_s2 = ft_strlen_p(s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		while (len_s1)
		*(--joined) = s1[--len_s1];
		ft_free(s1);
		ft_free(s2);
	}
	return (joined);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	len_s1 = ft_strlen_p(s1);
	len_s2 = ft_strlen_p(s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		while (len_s1)
		*(--joined) = s1[--len_s1];
		ft_free(s1);
	}
	return (joined);
}

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	len_s1 = ft_strlen_p(s1);
	len_s2 = ft_strlen_p(s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		while (len_s1)
		*(--joined) = s1[--len_s1];
		ft_free(s2);
	}
	return (joined);
}

char	*ft_strjoin_free_sep(char *s1, char *s2, char sep)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*joined;

	i = 1;
	if (s1 && s2)
		i = 2;
	len_s1 = ft_strlen_p(s1);
	len_s2 = ft_strlen_p(s2);
	joined = (char *)malloc((len_s1 + len_s2 + i) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2 + i - 1;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		if (i == 2)
			*(--joined) = sep;
		while (len_s1)
		*(--joined) = s1[--len_s1];
		ft_free(s1);
		ft_free(s2);
	}
	return (joined);
}

/*
int main()
{
	char	*test = "test1";
	char	*test2 = "test2";
	char	*m_test = ft_strdup(test);
	char	*m_test2 = ft_strdup(test2);
	char	*joined;

	joined = ft_strjoin_free_sep(NULL, m_test2, ' ');
	printf("joined sep = \"%s\"\n", joined);
	ft_free(joined);
	ft_free(m_test);
	// ft_free(m_test2);
}
*/
