# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 13:00:35 by dohyuki2          #+#    #+#              #
#    Updated: 2024/12/22 17:20:47 by dohyuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAG = -Wall -Wextra -Werror -g

INC = minishell.h

SRCS = minishell_parse.c \
		Utilities/utilities.c \
		Utilities/utilities2.c \
		Utilities/free.c \
		Utilities/free2.c \
		Utilities/error.c \
		Utilities/builtin/export_utils.c \
		Utilities/builtin/export_utils2.c \
		Utilities/builtin/export_utils3.c \
		Utilities/builtin/export_utils4.c \
		Utilities/builtin/list_utils.c \
		Utilities/builtin/pwd_utils.c \
		Utilities/builtin/pwd_utils2.c \
		Utilities/parsing/split.c \
		Utilities/parsing/token_utils.c \
		built_in/built_in.c \
		built_in/echo.c \
		built_in/env.c \
		built_in/exec.c \
		built_in/export.c \
		built_in/export_sort.c \
		built_in/pwd.c \
		built_in/unset.c \
		parse/check_param.c \
		parse/tokenize.c \
		parse/substitution.c \
		parse/env_tokenize.c \
		parse/env_tokenize2.c \
		parse/make_info.c \
		parse/here_doc.c \
		parse/quote.c \
		parse/dquote.c \
		parse/oper.c \
		parse/pipe.c \
		parse/space.c \
		parse/str.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $(NAME) $^ -lreadline

clean :
	rm -rf $(OBJS)

fclean :
	make clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re