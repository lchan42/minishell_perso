/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/07/06 13:02:04 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__visual_print_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
		while (tab[++i])
			printf("%d : %s\n",i , tab[i]);
}

void	__visual_print_lexer(t_list *lst)
{
	while (lst)
	{
		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("type = %d\n", ((t_lexer_token *)lst->content)->type);
		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1, "[", 1);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		write(1, "]", 1);
		printf("\n\n");
		lst = lst->next;
	}
}

/*
void	lexer_analyser(t_list *lexer)
{
	if(!lexer)
	{
		printf("leaving lexer\n");
		exit(1);
	}
}
*/
/*********************eventual question to ask:
 * concerning odd quotes, do nothing ? or ask for completion ?
 * lexer nods, Show I seperate words according to METACHAR or space?
 */


/**********************to do
 * lexer analyser : checking the conformity of type operator
 * 					attributing types
 */

/**********************
 * interrogation: concerning the error control function
 * before the construction of the t_list
 * during the construction of the t_list
 * after the construction of the t_list
 */


// t_list *lexer_loop(char *read, t_list *lexer)
// {
// 	while(!read)
// 	{
// 		if (!read)
// 		{
// 			read = get_next_line(0);
// 			*(read + ft_strlen(read) - 1) = '\0';
// 		}
// 		lexer = lexer_make(read);
// 	}
// 	return (lexer);
// }

// void	lexer_loop(t_list **read_lst, t_list **lexer)
// {
// 	char *read;
// 	t_list *new_content;

// 	read = NULL;
// 	while (!read)
// 		read = get_next_line(0);
// 	*(read + ft_strlen(read) - 1) = '\0';
// 	new_content = lexer_make(read);
// 	ft_lstadd_back(read_lst, ft_lstnew(read));
// 	ft_lstadd_back(lexer, new_content);
// }

// int main (int ac, char **av, char **envp)
// {
// 	//char *read;
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
// 	t_list *lexer;
// 	t_list *read_lst;

// 	lexer = NULL;
// 	read_lst = NULL;
// 	while (!lexer)
// 	{
// 		lexer_loop(&read_lst, &lexer);
// 		/*
// 		read = get_next_line(0);				//using gnl here rather than readline coz less leak
// 		*(read + ft_strlen(read) - 1) = '\0';	//replacing the \n by \0
// 		lexer = lexer_make(read);*/
// 	}
// 	//lexer_analyser(lexer);
// 	__visual_print_lexer(lexer);
// 	lexer_free(&lexer);

// 	//free(read)
// }
void	lexer_readline(char **read, char *prompt)
{
	while (!*read)
	{
		write(1, prompt, ft_strlen(prompt));
		*read = get_next_line(0);
		*(*read + ft_strlen(*read) - 1) = '\0';
		if (**read == '\0')
		{
			free(*read);
			*read = NULL;
		}
	}
}

void	lexer_loop(t_lexer_data *l_data)
{
	char *read;

	read = NULL;
	if (l_data->read_lst == NULL)
		lexer_readline(&read, FIRST_PROMPT);
	else
		lexer_readline(&read, SECOND_PROMPT);

	ft_lstadd_back(&l_data->read_lst, ft_lstnew(read));
	lexer_make(l_data, read);
}

int main (int ac, char **av, char **envp)
{
	//char *read;
	(void) ac;
	(void) av;
	(void) envp;
	t_lexer_data	l_data;

	l_data.lexer = NULL;
	l_data.read_lst = NULL;
	//while (!l_data.lexer)
	lexer_loop(&l_data);
	__visual_print_lexer(l_data.lexer);
	lexer_data_free(&l_data);
}
