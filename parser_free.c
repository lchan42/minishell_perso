/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:02 by slahlou           #+#    #+#             */
/*   Updated: 2022/07/19 12:52:28 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__t_list_free(t_list **lst)
{
	t_list  *runner;

	if (*lst)
	{
		runner = *lst;
		while (runner)
		{
			if ((*lst)->content)
				free((*lst)->content);
			runner = runner->next;
			free(*lst);
			*lst = runner;
		}
	}
	*lst = NULL;
}

void	__free_io(t_io io_struct)
{
	//if ((io_struct).arg)
	//	free((io_struct).arg);
	if ((io_struct).stock)
		__t_list_free(&((io_struct).stock));
	if ((io_struct).here_buffer)
		__t_list_free(&((io_struct).here_buffer));
}

void	__free_parse(t_splcmd **head)
{
	t_splcmd *runner;

	runner = *head;
	if (*head)
	{
		while (runner)
		{
			__free_io(runner->in);  // add ft_free_in to free what is inside in_struct
			__free_io(runner->out); // add ft_free_out to free what is inside out_struct
			//	free(runner->cmd); // add ft_free_cmd to free what is inside cmd_struct
			runner = runner->next;
			free(*head);
			*head = runner;
		}
		*head = NULL;
	}
}
