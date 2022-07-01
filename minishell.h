/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:36 by lchan             #+#    #+#             */
/*   Updated: 2022/07/01 16:01:57 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libraries/libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


# define METACHAR "|&()<>" 		//dont need to interpreat';'
# define LOG_META "|&"
# define RED_META "<>"
# define AND_IF "&&"
# define OR_IF "||"
# define DLESS "<<"					//heredoc
# define DGREAT ">>"				//redirect exit in append mode
# define SQUOTE '\''			//meta char in simple quote should be interpreted as normal char
# define DQUOTE '\"'			//same as single, expect for $ sign;
# define DOLLAR "$"				//if followed by a string, go in the env

//recode function strtok_r
// ast tree node type ; https://github.com/vorpaljs/bash-parser/blob/master/documents/ast.md


//char *readline (const char *prompt); (need to be compile with the flag -lreadline)
// rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history,

// signal, typedef void (*sighandler_t)(int);
// sigaction,
// sigemptyset,
// sigaddset,
// kill,        int kill(pid_t pid, int sig);

// getcwd,
// chdir,

// stat, get stat of a
// lstat,
// fstat,

// opendir, open directory
// readdir, read directory
// closedir, close directory

// isatty,
// ttyname,
// ttyslot,
// ioctl,

// getenv, char *getenv(const char *name) --> for the $USER

// tcsetattr,
// tcgetattr,
// tgetent,
// tgetflag,
// tgetnum,
// tgetstr,
// tgoto,
// tputs
//void	__make_token (char *str, const char delim);

enum e_lexer_error
{
	ERR_SOLO_QUOTE = 1,
	ERR_TYPE_CHECKER,
	ERR_UNEXPECTED_TOKEN = 5,
	//ERR_UNACCEPTED_TOKEN,
	ERR_MALLOC_FAIL				//is error is not due to the user. It should shut down the whole process.
};

enum e_lexer_type_token
{
	TYPE_LEXER_WORD,
	TYPE_LEXER_OPERATOR,
	TYPE_LEXER_OPERATOR_LOGICAL,
	TYPE_LEXER_OPERATOR_REDIRECT,
};

typedef struct s_lexer_token
{
	unsigned int	index;
	int				type;
	char			*start;
	char			*end;
	size_t			length;

}				t_lexer_token;

int		lexer_set_ptrs(char **start, char **end);
t_list	*lexer_make(char *str);
void	lexer_free(t_list *lexer);
void	lexer_error(t_list **lexer, int error_id, t_lexer_token *tmp_nod);
int		lexer_type_checker(t_list **lexer_head, t_lexer_token *tmp_nod);
#endif
