/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:14:27 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 14:58:19 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void *malloc_elem)
{
	if (malloc_elem)
		free (malloc_elem);
}

void	ft_free_setnull(void **malloc_elem)
{
	if (malloc_elem && *malloc_elem)
	{
		free(*malloc_elem);
		*malloc_elem = NULL;
	}
}
