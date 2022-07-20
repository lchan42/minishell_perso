/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_save.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:55:50 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/20 15:56:31 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_io_arg(t_io *io)
{
	ft_lstadd_back(&(io->stock), ft_lstnew(io->arg));
}

static void	save_here_d(t_io *io)
{
	char	*limit;
	char	buf[BUFFER_S];
	int		read_ret;

	limit = io->arg;
	read_ret = 1;
	if (io->here_buffer)
		__t_list_free(&(io->here_buffer));
	while (read_ret)
	{
		write(1, "> ", 2);
		read_ret = read(0, buf, BUFFER_S);
		buf[read_ret] = '\0';
		if (!(ft_strncmp(buf, limit, read_ret - 1)))
			break ;
		ft_lstadd_back(&(io->here_buffer), ft_lstnew(ft_strdup(buf)));
	}
	free(io->arg);
	io->arg = NULL;
}

static void	__init_stock_mgmt(void(*stock_mgmt[7])(t_io *io))
{
	stock_mgmt[IN_D] =  &save_io_arg;
	stock_mgmt[HERE_D] = &save_here_d;
	stock_mgmt[OUT_D] = &save_io_arg;
	stock_mgmt[OUT_D_APP] = &save_io_arg;
}

t_list	*__get_stock(t_io *io, int type)
{
	void	(*stock_mgmt[7])(t_io *io);
	__init_stock_mgmt(stock_mgmt);
	stock_mgmt[type](io);
	return (io->stock);
}
