top : minishell

SRC = $(wildcard *.c)

minishell : $(SRC)
	$(CC) -lreadline -g $^ -o $@

re :
	rm minishell
	$(MAKE)
