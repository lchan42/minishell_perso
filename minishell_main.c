/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:13:14 by lchan             #+#    #+#             */
/*   Updated: 2022/07/20 14:44:39 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_readline_add_history(char *prompt)
{
	char	*usr_input;

	usr_input = NULL;
	while (!usr_input)
	{
		usr_input = readline(prompt);
		if (!*usr_input)
			ft_free_char(&usr_input);
	}
	add_history(usr_input);
	return (usr_input);
}

int	main (int ac, char **av, char **envp) //simulation of what should minishell main look like
{
	(void) ac;
	(void) av;
	(void) envp;
	t_data			msh_data;
//	char			*usr_input;
//	t_lexer_data	*lexer_data;

	//initminishell
//	while (1)
//	{
		msh_data.user_input = ft_readline_add_history(FIRST_PROMPT);
		msh_data.lexer_data = lexer(msh_data.user_input);
		msh_data.parser = __parser(msh_data.lexer_data->lexer);
		//expander
		//redirection
		//executor
		if (msh_data.lexer_data)
		{
			//__visual_print_lexer(msh_data.lexer_data->lexer);
			//__visual_print_read_lst(msh_data.lexer_data->read_lst);
			lexer_data_free(&msh_data.lexer_data);
		}
		if (msh_data.parser)
		{
			__visual_print_splcmd(msh_data.parser);
			__free_parse(&(msh_data.parser));
		}
//	}
}
