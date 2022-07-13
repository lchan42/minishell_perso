/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:03:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 12:39:48 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llist	*ft_llstnew(void *content)
{
	t_llist	*tmp;

	tmp = malloc(sizeof(t_llist));
	if (!tmp)
		return (NULL);
	tmp->content = content;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}
