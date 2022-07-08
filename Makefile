# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchan <lchan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 20:57:58 by lchan             #+#    #+#              #
#    Updated: 2022/07/08 19:46:08 by lchan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBPATH = ./libraries/libft
LIB	= ./libraries/libft/libft.a

SRCS	=	main.c\
			lexer_set_ptrs.c\
			lexer_make.c\
			lexer_error.c\
			lexer_add_history.c


SRCSBONUS =

NAME		= lexer
HEADER		= minishell.h

OBJS		= ${SRCS:.c=.o}

OBJSBONUS	= ${SRCSBONUS:.c=.o}
%.o: %.c
			${CC} -g3 ${CFLAGS} -c $< -o $@

CC			= gcc
MAKE		= make
RM			= rm -f
CFLAGS		= -Wall  -Wextra -g3
DEBUGFLAGS	= -g3 #-fsanitize=address


all:		${NAME}

${OBJS}:	${HEADER}

$(NAME):	${OBJS}
			${MAKE} -C ${LIBPATH} all
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} -L${LIBPATH} -lreadline



debug:		${OBJS}
			${MAKE} -C ${LIBPATH} all
			${CC} ${DEBUGFLAGS} -o ${NAME} ${OBJS} ${LIB} -L${LIBPATH}

g3:			${OBJS}
			${MAKE} -C ${LIBPATH} all
			${CC} -g3 -o ${NAME} ${OBJS} ${LIB} -L${LIBPATH}

bonus:		${NAME} ${OBJS} ${OBJSBONUS}
			${AR} ${ARFLAGS} ${NAME} ${OBJSBONUS}

cleanlib :
			${MAKE} -C ${LIBPATH} clean

clean:		cleanlib
			${RM} ${OBJS} ${OBJSBONUS}

cleanb:		clean
			${RM} ${OBJSBONUS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

c:			all clean

.PHONY:		re clean fclean all bonus



################Just a reminder for my self################################
#
# %.o: %.c means anytext.o depends on that sametext.c
# 		it shows how to create a .o
# $@ whatever is on the left side of the rule (%.o)
# $^ whatever is on the right side of the rule colomn (%.c)
#
#----------------There are seven “core” automatic variables:---------------
#
#$@: The filename representing the target.
#
#$%: The filename element of an archive member specification.
#
#$<: The filename of the first prerequisite.
#
#$?: The names of all prerequisites that are newer than the target,
#	separated by spaces.
#
#$^: The filenames of all the prerequisites, separated by spaces.
#	 This list has duplicate filenames removed since for most uses,
#	 such as compiling, copying, etc., duplicates are not wanted.
#
#$+: Similar to $^, this is the names of all the prerequisites
#	 separated by spaces, except that $+ includes duplicates.
#	 This variable was created for specific situations such as arguments
#	 to linkers where duplicate values have meaning.
#
#$*: The stem of the target filename. A stem is typically a filename
#	 without its suffix. Its use outside of pattern rules is discouraged.
#
#------------------------------man make ----------------------------------
#-C : open a make inside a folder
#	  (can also do --directory=dir (dir = folders name ./librairie/libft))
#
##########################################################################
