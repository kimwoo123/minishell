#include "../inc/minishell.h"

int g_status;

int	main(int argc, char **argv, char **envp)
{
	char	*command_line;

	while (1)
	{
		command_line = readline("minishell> ");
		if (!command_line)
			break ;
		scan_command(command_line);
		add_history(command_line);
		free(command_line);
		system("leaks --list -- $PPID");
		command_line = NULL;
	}
	return (0);
}
