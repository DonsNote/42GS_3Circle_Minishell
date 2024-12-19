NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
FILES = env.c utils.c export.c free.c export_sort.c list.c

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
				@${CC}	${CFLAGS}	${OBJS}	-o	${NAME}

clean:
				$(RM)	$(OBJS)

fclean:	clean
				$(RM)	$(NAME)

re:				fclean	all

.PHONY: all	clean	fclean	re