/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:26:44 by lchan             #+#    #+#             */
/*   Updated: 2022/07/20 17:26:18 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	lexer_readline(char **usr_input, char *prompt)
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
*/

void	__lexer_end_pipe_check(t_llist **lexer)
{
	t_llist	*tmp;

	tmp = ft_llstlast(*lexer);
	if (!tmp || *lexer == tmp)
		return;
	if (((t_lexer_token *)tmp->content)->type == TYPE_LEXER_OPERATOR_LOGICAL)
	{
		printf("minishell: syntax error near unexpected token '%.*s'\n",
		(int)(((t_lexer_token *)tmp->content)->length),
		((t_lexer_token *)tmp->content)->start);
		lexer_free(lexer);
	}
}

// static t_lexer_data	*lexer_data_init(char	*usr_input)
// {
// 	t_lexer_data	*lexer_data;

// 	lexer_data = malloc(sizeof(t_lexer_data));
// 	if (lexer_data)
// 	{
// 		lexer_data->lexer = NULL;
// 		lexer_data->read_lst = NULL;
// 		ft_llstadd_back(&lexer_data->read_lst, ft_llstnew(usr_input));
// 	}
// 	return (lexer_data);
// }

/*
static t_llist	*lexer_init(char	*usr_input)
{
	t_lexer_data	*lexer_data;

	lexer_data = malloc(sizeof(t_lexer_data));
	if (lexer_data)
	{
		lexer_data->lexer = NULL;
		lexer_data->read_lst = NULL;
		ft_llstadd_back(&lexer_data->read_lst, ft_llstnew(usr_input));
	}
	return (lexer_data);
}*/

t_llist	*lexer(char *usr_input)
{
	t_llist	*lexer;

	//lexer_data = lexer_init(usr_input);
	lexer = NULL;
	lexer_make(&lexer, usr_input);
	if (lexer)
		__lexer_end_pipe_check(&lexer);
	return (lexer);
}

// t_lexer_data	*lexer(char *usr_input)
// {
// 	t_lexer_data	*lexer_data;

// 	lexer_data = lexer_data_init(usr_input);
// 	if (lexer_data)
// 	{
// 		lexer_make(&lexer_data, usr_input);
// 		__lexer_end_pipe_check(&lexer_data->lexer);
// 	}
// 	return (lexer_data);
// }


/*
void	lexer_loop(t_lexer_data *lexer_data)
{
	char *usr_input;

	usr_input = NULL;
	lexer_readline(&usr_input, LEXER_PROMPT);
	ft_llstadd_back(&lexer_data->read_lst, ft_llstnew(usr_input));
	lexer_add_history(lexer_data->read_lst);
	lexer_make(lexer_data, usr_input);
}*/

/*
void	msh_init_cpy_envp(int	size, char **envp)
{

}

void	msh_init_data(t_msh_data *msh_data, char **envp)
{
	msh_data->user_input = NULL;
	msh_data->env_size = 0;
	msh_data->env = envp;
	msh_data->lexer_data = NULL;
}

char	**msh_init (t_msh_data *msh_data, char **envp)
{
	msh_init_data(msh_data);
	msh_init_cpy_envp(&msh_data->env_size, &msh_data->env);
	//set all value to null;
}
*/
/******************FUNCTION THAT ARE NOT SUPPOSED TO BE IN THE LEXER_MAIN**********************/



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











/*************************
 * minishell so far:
 * lexer
 * 		break our entry into words and operator type. uses a t_llist that will have to be freed
 * Parser
 * 		prepare the filed so the fork/execve emperor can do its job easily
 * 			--> creat a t_list of simple command
 * 			--> each simple command in another lst. each nod will have a type. (redirection, cmd, arg, operator)
 * expand
 * 			-->changing the content of words token
 * 			-->quote removal
 * redirection
 * 			-->in this part we have to open and close the files that are being redirected.
 * 					if we have several redirection of the same STD
 * 			-->after any redirection is performed, the nod of the redirection will be destroyed.
 * 				at the end any simple command will only contain words token
 * 			--> 2nd read :
 * execusion
 * 			--> sending the
*/



/*************************
 * questions :
 *
 * */
/****************************parsing:*****************************
if word :
	check builting : if first word is builtin,
	check expand

if redictection:
	check
	check heredoc, attribute heredoc
	some test about redirection :
		<<a <<b >created1 <<c
			in this test heredoc 1 2 3 are created before created1 file.
			conclusion	--> parsing is creating heredoc only.
						--> creation of other file are done in redirection part
		<<a <<b     >created1 <unexistingfile >created2 <<c
			this test prove the conclusion above
			heredoc 1 2 3 are asked, then created1 is O_CREAT but the redirection stops at open("unexistingfile")
			message = "bash: unexistingfile: No such file or directory"
	--> parsing is associating redirection with there respective files. If the redirection in an here_doc, the heredoc creation happens.
*/
