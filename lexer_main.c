/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:26:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/12 12:57:15 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_readline(char **usr_entry, char *prompt)
{
	while (!*usr_entry)
	{
		*usr_entry = readline(prompt);
		if (**usr_entry == '\0')
		{
			free(*usr_entry);
			*usr_entry = NULL;
		}
	}
}

void	lexer_loop(t_lexer_data *l_data)
{
	char *usr_entry;

	usr_entry = NULL;
	lexer_readline(&usr_entry, LEXER_PROMPT);
	ft_lstadd_back(&l_data->read_lst, ft_lstnew(usr_entry));
	lexer_add_history(l_data->read_lst);
	lexer_make(l_data, usr_entry);
}

t_lexer_data	*l_data_init(char	*usr_entry)
{
	t_lexer_data	*l_data;

	//l_data = NULL;
	l_data = malloc(sizeof(t_lexer_data));
	if (l_data)
	{
		l_data->lexer = NULL;
		l_data->read_lst = NULL;
		ft_lstadd_back(&l_data->read_lst, ft_lstnew(usr_entry));

	}
	return (l_data);
}

t_lexer_data	*lexer(char *usr_entry)
{
	t_lexer_data	*l_data;

	l_data = l_data_init(usr_entry);
	if (l_data)
		lexer_make(l_data, usr_entry);
	return (l_data);
}

/******************FUNCTION THAT ARE NOT SUPPOSED TO BE IN THE LEXER_MAIN**********************/
char	*ft_readline_add_history(char *prompt)
{
	char	*usr_entry;

	usr_entry = NULL;
	while (!usr_entry)
	{
		usr_entry = readline(prompt);
		if (!*usr_entry)
			ft_free_char(&usr_entry);
	}
	add_history(usr_entry);
	return (usr_entry);
}

int	main (int ac, char **av, char **envp) //simulation of what should minishell main look like
{
	(void) ac;
	(void) av;
	(void) envp;
	char			*usr_entry;
	t_lexer_data	*l_data;
	while (1)
	{
		usr_entry = ft_readline_add_history(FIRST_PROMPT);
		l_data = lexer(usr_entry);
		//parser
		//expander
		//executor
		if (l_data)
		{
			__visual_print_lexer(l_data->lexer);
			__visual_print_read_lst(l_data->read_lst);
			lexer_data_free(l_data);
		}
	}
}

/*****lexer*****/
//open of heredoc has to be done in lexer. -->internal getnextline with no tmp file. redirect cant be done after via a pipe.
//decide what to do if malloc error.
//decide what to do with single & --> considered as word ?


// exit function, if usr entry = "exit";
//
// expand se fait apres le parsing. Ne pas gerer les parentheses. tout expand est considere comme un mot. meme si on a $PIPE = '|'
//include t_data dans le lexer
//add some build in




//lexer : here to check if token is operator or words. also check syntax error.

//if here doc, nextword = limiteur


//parser : gives a more precise type to words. the first word encountered is a type cmd, other are args.
