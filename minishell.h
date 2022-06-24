/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:36 by lchan             #+#    #+#             */
/*   Updated: 2022/06/24 19:35:55 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libraries/libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
#include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


# define METACHAR "|&()<>" 		//dont need to interpreat';'
# define S_QUOTE "'"			//meta char in simple quote should be interpreted as normal char
# define D_QUOTE "\""			//same as single, expect for $ sign;
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


typedef enum e_lexer_type_token
{
	TYPE_LEXER_WORD,
	TYPE_LEXER_EXPAND,
	TYPE_LEXER_OPERATOR
}			t_lexer_type_token;

typedef struct s_lexer_token
{
	int				index;
	unsigned int	type;
	char			*start;
	char			*end;
	size_t			length;

}				t_lexer_token;

char	**__make_token(char *str, const char *delim);
void lexer_creat_lst(t_list **lexer_lst);
void	lexer_reader(char **start, char **end);
#endif
