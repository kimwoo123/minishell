top : minishell

SRC = $(wildcard *.c)



minishell : $(SRC)
	$(CC) -L ../libft -lft -lreadline -g -fsanitize=address $^ -o $@

re :
	rm minishell
	$(MAKE)
