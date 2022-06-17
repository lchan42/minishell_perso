/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/06/17 21:29:39 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__visual_print_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
		while (tab[++i])
			printf("%s\n", tab[i]);
}

int main (int ac, char **av, char **envp)
{
	char *read;
	char **token_tab;
	(void) ac;
	(void) av;
	(void) envp;

 	read = readline("test : ");
	token_tab = __make_token(read, " +-");
	__visual_print_tab(token_tab);
	free(read);
}
