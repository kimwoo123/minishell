.DEFAULT_GOAL := all

NAME		= minishell

SRC = $(wildcard *.c)

minishell : $(SRC)
	$(CC) -L ../libft -lft -lreadline -g -fsanitize=address $^ -o $@ -I ../inc

all: $(NAME)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(NAME)
	$(RM) -r minishell.dSYM

re :
	$(RM) $(NAME)
	$(MAKE) all

.PHONY: all clean fclean re
