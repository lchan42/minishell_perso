/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:13:14 by lchan             #+#    #+#             */
/*   Updated: 2022/07/25 16:58:31 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__init_msh(t_data *msh_data)
{
	msh_data->log_fd = 0;
	msh_data->env = NULL;
	msh_data->exp = NULL;
	msh_data->user_input = NULL;
	msh_data->lexer = NULL;
	msh_data->parser = NULL;
}

void __set_msh_data(t_data *msh_data, char **envp)
{
	int	envp_size;
	char **env;

	__init_msh(msh_data);
	envp_size = ft_strtablen(envp);
	env = ft_calloc(sizeof(char *), envp_size + 2);
	if (env)
	{
		*env = ft_calloc(sizeof(char), 2);
		if (*env)
		{
			*(*(env + 0) + 0) |= envp_size;
			*(*(env + 0) + 1) |= envp_size >> 8;
		}
		env++;
		while(*envp)
			*(env++) = ft_strdup(*(envp++));
		*env = NULL;
	}
	msh_data->env = env - envp_size;
	// --(msh_data->env);
	// printf("ICI %d %d\n", (short)**((msh_data->env)), (short)*(*((msh_data->env)) + 1));
	// while (*(msh_data->env))
	// {
	// 	printf("%s\n", *((msh_data->env)++));
	// 	//printf("coucou\n");
	// }
}

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

	__set_msh_data(&msh_data, envp);
	//while (1)
	//{
		msh_data.user_input = ft_readline_add_history(FIRST_PROMPT);
		msh_data.lexer = lexer(msh_data.user_input);
		msh_data.parser = __parser(msh_data.lexer);
		msh_data.parser = __expand(msh_data.parser, msh_data.env);
		//redirection
		//executor
		if (msh_data.parser)
		{
			__visual_print_splcmd(msh_data.parser, msh_data.lexer);
			__free_parse(&(msh_data.parser));
		}
		if (msh_data.lexer)
		{
			//__visual_print_lexer(msh_data.lexer_data->lexer);
			//__visual_print_read_lst(msh_data.lexer_data->read_lst);
			lexer_free(&msh_data.lexer);
		}

		if (msh_data.user_input)
			ft_free_char(&msh_data.user_input);
	//}
	if (msh_data.env)
			ft_free_strtab((msh_data.env) - 1);
}

