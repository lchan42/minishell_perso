/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:54:02 by lchan             #+#    #+#             */
/*   Updated: 2022/07/05 18:25:34 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
