/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/06/15 18:16:10 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__visual_print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*read;
// 	char	*token;
// 	char	*tab[100];

// 		read = readline("test : ");
// 		printf("%p, %s\n", read, read);

// 			token = strtok(read, " ");
// 			printf("%p, %s\n", token, token);
// 			token = strtok(NULL, " ");
// 			printf("%p, %s\n", token, token);
// 			token = strtok(read, " ");
// 			printf("%p, %s\n", token, token);

// 		__visual_print_tab(tab);
// 		free(read);
// 	return (0);
// }

int main (int ac, char **av, char **envp)
{
	char *read;
	char **token_tab;

 	read = readline("test : ");
	token_tab = __make_token(read, " +-");
	__visual_print_tab(token_tab);
		free(read);
}
