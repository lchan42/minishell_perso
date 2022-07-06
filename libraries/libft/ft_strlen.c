/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:22:14 by lchan             #+#    #+#             */
/*   Updated: 2022/07/05 14:56:41 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*
size_t	ft_strlen(const char *s)
{
	char *tmp;

	tmp = (char *)s;
	while (tmp)
		tmp++;
	return (tmp - s);
}
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
