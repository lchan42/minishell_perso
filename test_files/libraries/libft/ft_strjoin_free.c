/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:54:02 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 12:53:38 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	*ft_strjoin_free(char *s1, char *s2)
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
	free(s1);
	free(s2);
	return (joined);
}
*/

/**
 * @brief
 *
 * @param s1
 * @param s2
 * @return char* if !s1 || !s2 act as ft_strdup if !s1 && !s2, returns "\0"
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		while (len_s1)
		*(--joined) = s1[--len_s1];
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
	return(joined);
}

int main()
{
	char	*str1 = NULL;
	char	*str2 = NULL;

	printf("joined = \"%s\"\n", ft_strjoin_free(str1, str2));
}
