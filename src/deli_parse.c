# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

#define DELIMETER "<>|"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

size_t	trim_line(const char *line)
{
	size_t	index;

	index = 0;
	while (line[index] && is_space(line[index]))
		index++;
	return (index);
}

static int	is_delimiter(char c)
{
	int	index;

	index = 0;
	while (DELIMETER[index])
	{
		if (DELIMETER[index] == c)
			return (1);
		index++;
	}
	return (0);
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

char	*ft_strdup(const char *s1)
{
	char	*addr;
	int		i;

	addr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (addr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		addr[i] = s1[i];
	addr[i] = '\0';
	return (addr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char *ft_strndup(const char *begin, size_t size)
{
	char	*result;
	size_t	index;

	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	index = 0;
	while (index < size)
	{
		result[index] = begin[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

void	check_quote(char c, char *flag)
{
	if (*flag && *flag == c)
		*flag = '\0';
	else if (!*flag && is_quote(c))
		*flag = c;
}

void	get_token(const char *line, size_t size)
{
	printf("token: %s\n", ft_strndup(line, size));
}

void	seperate_meta(const char *line, size_t size)
{
	size_t	index;
	size_t	start_index;

	index = trim_line(&line[0]);
	start_index = index;
	if (is_delimiter(line[index]))
	{
		while (index < size && is_delimiter(line[index]))
			index++;
		get_token(&line[start_index], index - start_index);
		if (size != index)
			get_token(&line[index], size - index);
	}
	else
		get_token(&line[index], size - index);
}

char *parse_space(const char *line, size_t size)
{
	size_t	index;
	size_t	start_index;
	int		space_flag;
	char	quote_flag;

	space_flag = 0;
	quote_flag = '\0';
	index = 0;
	start_index = 0;
	while (index < size)
	{
		check_quote(line[index], &quote_flag);
		if (!quote_flag && (space_flag && is_space(line[index])))
		{
			seperate_meta(&line[start_index], index - start_index);
			start_index = index;
			space_flag = 0;
		}
		else if (!quote_flag && (!space_flag && !is_space(line[index])))
			space_flag = 1;
		++index;
	}
	if (space_flag)
		seperate_meta(&line[start_index], index - start_index);
	return (ft_strndup(line, size));
}

int	repeat_meta(char *line, size_t index)
{
	if (index > 0)
		if (!ft_strncmp(&line[index - 1], "<<" , 2) || !ft_strncmp(&line[index - 1], ">>", 2))
			return (1);
	return (0);
}

int	parse_command(char *line)
{
	size_t	index;
	size_t	start_index;
	char	quote_flag;
	char	*token;

	quote_flag = '\0';
	start_index = 0;
	index = -1;
	while (line[++index])
	{
		check_quote(line[index], &quote_flag);
		if ((!quote_flag && is_delimiter(line[index])) && !repeat_meta(line, index))
		{
			token = parse_space(&line[start_index], index - start_index);
			printf("str: %s\n", token);
			start_index = index;
		}
	}
	token = parse_space(&line[start_index], index - start_index);
	if (quote_flag)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command_line;

	while (1)
	{
		command_line = readline("minishell> ");
		if (!command_line)
			break ;
		parse_command(command_line);
		add_history(command_line);
		free(command_line);
		command_line = NULL;
	}
	return (0);
}
