/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:16:33 by lchan             #+#    #+#             */
/*   Updated: 2022/07/16 20:21:32 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

t_io *__init_in(int type, t_llist *lexer)
{
	t_io *new_io;

	new_io = ft_calloc(1, sizeof(t_io));
	
}