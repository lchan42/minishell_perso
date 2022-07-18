/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:36 by lchan             #+#    #+#             */
/*   Updated: 2022/07/18 17:25:24 by slahlou          ###   ########.fr       */
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

# define FIRST_PROMPT "test_prompt : "
# define LEXER_PROMPT "> "
# define METACHAR "|<>" 		//dont need to interpreat';'
# define LOG_META "|&"
# define RED_META "<>"

# define AND_IF "&&"				// if left true, do right
# define OR_IF "||"					// if left faulse do right


/*
# define LESS "<"`					//in redirection
# define GREAT ">"					//out redirection
# define DLESS "<<"					//redirection heredoc
# define DGREAT ">>"				//redirect exit in append mode
*/


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
	ERR_SET_PTR = 1,
	ERR_SOLO_QUOTE,
	ERR_SYNTAX,
	//ERR_SYNTAX_NL,
};

enum e_lexer_type_token
{
	TYPE_LEXER_WORD = 1,
	TYPE_LEXER_OPERATOR_LOGICAL,
	TYPE_LEXER_OPERATOR_REDIRECT,
	TYPE_LEXER_SYNTAX_ERR
};

typedef struct s_lexer_token
{
	unsigned int	index;
	int				type;
	char			*start;
	char			*end;
	size_t			length;
}				t_lexer_token;

typedef struct s_lexer_data
{
	t_llist *lexer;
	t_llist *read_lst;
}			t_lexer_data;



/**********************************parsing struct*****************************************/
enum	e_parser_io_type
{
	IN_D = 1, // basic infile redirect
	HERE_D, // here_doc
	PIPE_IN,
	OUT_D, // basic outfile redirect
	OUT_D_APP, // append redirect mode
	PIPE_OUT
};

enum	e_parser_cmd_type
{
	BUILTIN,
	BUILTOUT
};

typedef struct s_io
{
	int		type; // less or dless for in or great dgreat for output
	char	*arg; //file name or lim (heredoc) max file name linux = 255 but if heredoc, no limits
	int		fd; //0 by default (in) or 1 by default for (out)
	t_list	*stock; //heredoc buffer (if in) AND lst of file name that have to be open (if out)
}				t_io;

typedef struct s_cmd
{
	int		type; //builtin or not
	int		size; //len of cmd_words (number of lines)
	char	**cmd_words; //contains 0 path (path + cmd ex: /usr/bin/cat) followed by one arg per line
}				t_cmd;

typedef struct s_splcmd
{
	t_io			*in;
	t_io			*out;
	t_cmd			*cmd;
	struct s_splcmd	*next;
}	t_splcmd;


/***************************BROUILLON utile ?? ****************************/
typedef struct s_here_doc_data
{
	t_llist	*heredoc;
	int		*here_doc_pipe; //gonna be close after the first child.
}t_here_doc_data;

typedef struct s_data
{
	char			*user_input;
	int				env_size;
	char			**env;
	t_lexer_data	*lexer_data;

}t_data;

/*typedef struct s_data //////////////////his is the main structure. it's going to be in stack;
{
	// t_ast				*list_cmd;
	// t_error_state		errors;
	// t_llist				*list_env_token;
	// t_llist				*lexer_fake_token_list;
	t_lexer_data		*lexer_data;
	t_here_doc			*here_doc_data;
	// t_llist				*garbage_collector;
	// t_program_params	main;
	// char				*program_folder;
	// char				current_folder[4096];
	// char				*builtin_folder;
	// char				*prompt_display;
	// int					status_last_cmd;
	// char				*string_type[TYPE_MAX];
}				t_data;
*/

int		lexer_set_ptrs(char **start, char **end);
void	lexer_make(t_lexer_data **lexer_data, char *str);
int		lexer_error(int error_id, t_lexer_token *current);
int		lexer_type_checker(t_llist **lexer_head, t_lexer_token *tmp_nod);


void	lexer_add_history(t_llist *read_lst);

void	lexer_free(t_llist **lexer);
void	t_llist_free(t_llist **lexer);
void	lexer_data_free(t_lexer_data **lexer_data);



/*************** parser *********************/
t_splcmd	*__parser(t_llist *lexer);
//void __init_in(t_io **in, t_llist *lexer);
void __init_io(t_io **in, t_io **out, t_llist *lexer);


			/**free**/
void __free_parse(t_splcmd **head);

/************* visual functions ****************/
void	__visual_print_tab(char **tab);
void	__visual_print_lexer(t_llist *lst);
void	__visual_print_read_lst(t_llist *usr_input);
void	__reverse_visual_print_lexer(t_llist *lst);
void	__visual_print_splcmd(t_splcmd *head);

#endif



//test1 | test2 | test 4 | test

//<<LIMIT test1 | test2 | test 4 | test







/******************* A VALIDER AVEC SASHA ***********************/

enum e_redirection
{
	REDIR_LESS,
	REDIR_DLESS,
	REDIR_GREAT,
	REDIR_DGREAT,
};

typedef struct s_redirect_token
{
	int		type;				//enum redirection
	char	*file;				//the char * of the redirection
	int		redirect_fd;		//for the open
}	t_redirect_token;

enum e_words
{
	WORD_CMD,					//the first word found(that is not part of here doc)
	WORD_ARG,					//other type word found
	WORD_EXPAND_CMD,
	WORD_EXPAND_ARG,
};

typedef struct s_word_token
{
	int			type;
	char		**info;		//type of the expand
	t_list		*expand;		//position of the expand ?
	t_list		*expand_env_adr;//position of the expand in the env ? NULL if non ?
}	t_word_token;

typedef struct s_parser
{
	int		nbr_splcmd;
	t_list	*splcmd_lst; 	//[simple cmd1]-[|]-[simple cmd2]-[|]-[simple cmd3]
	int		*execve_order;	//if bonus and priorities ?
}	t_parser;

//example <<a cat >outfile | grep '$USER' | cat > outfile

//lexer (<<a cat >outfile -e)
//		([redirect]-[word]-[word]-[word]-[redirect]-[word])
//parser splcmd_lst nod 1 =
//		([redirect]-[cmd]-[redirect]-[arg])
//		(redirection a ete join au word suivant)

//parser splcmd_

//[simple cmd1]-[|]-[simple cmd2]-[|]-[simple cmd3]

