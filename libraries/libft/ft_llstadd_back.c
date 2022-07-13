/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:02:39 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 12:49:55 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llstadd_back(t_llist **alst, t_llist *new)
{
	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
			ft_llstlast(*alst)->next = new;
	}
}
