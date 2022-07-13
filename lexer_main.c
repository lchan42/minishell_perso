/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:26:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 17:25:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_readline(char **usr_input, char *prompt)
{
	while (!*usr_input)
	{
		*usr_input = readline(prompt);
		if (**usr_input == '\0')
		{
			free(*usr_input);
			*usr_input = NULL;
		}
	}
}

void	lexer_loop(t_lexer_data *l_data)
{
	char *usr_input;

	usr_input = NULL;
	lexer_readline(&usr_input, LEXER_PROMPT);
	ft_llstadd_back(&l_data->read_lst, ft_llstnew(usr_input));
	lexer_add_history(l_data->read_lst);
	lexer_make(l_data, usr_input);
}

t_lexer_data	*l_data_init(char	*usr_input)
{
	t_lexer_data	*l_data;

	//l_data = NULL;
	l_data = malloc(sizeof(t_lexer_data));
	if (l_data)
	{
		l_data->lexer = NULL;
		l_data->read_lst = NULL;
		ft_llstadd_back(&l_data->read_lst, ft_llstnew(usr_input));

	}
	return (l_data);
}

t_lexer_data	*lexer(char *usr_input)
{
	t_lexer_data	*l_data;

	l_data = l_data_init(usr_input);
	if (l_data)
		lexer_make(l_data, usr_input);
	return (l_data);
}










/******************FUNCTION THAT ARE NOT SUPPOSED TO BE IN THE LEXER_MAIN**********************/
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
	char			*usr_input;
	t_lexer_data	*l_data;

	//initminishell
	while (1)
	{
		usr_input = ft_readline_add_history(FIRST_PROMPT);
		l_data = lexer(usr_input);
		//parser
		//expander
		//executor
		if (l_data)
		{
			__visual_print_lexer(l_data->lexer);
			__visual_print_read_lst(l_data->read_lst);
			//__reverse_visual_print_lexer(l_data->lexer);
			lexer_data_free(l_data);
		}
	}
}

/*****lexer*****/
//to fix: the reloop is done after the heredoc.
//open of heredoc has to be done in lexer. -->internal getnextline with no tmp file. redirect cant be done after via a pipe.
//decide what to do if malloc error.
//decide what to do with single & --> considered as word ?


// exit function, if usr entry = "exit";
//
// expand se fait apres le parsing. Ne pas gerer les parentheses. tout expand est considere comme un mot. meme si on a $PIPE = '|'
//include t_data dans le lexer
//add some build in




//lexer : here to check if token is operator or words. also check syntax error.


/*******here_doc********/
//if here doc, nextword = limiteur. --> if $USER, the limiter is "$USER" not the expended version.


//parser : gives a more precise type to words. the first word encountered is a type cmd, other are args.
