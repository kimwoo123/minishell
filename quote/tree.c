#include "tree.h"

static t_list	*create_element(int type, char *content);

void	lst_addback(t_list **list, t_list *node)
{
	t_list	*temp;

	if (!(*list))
	{
		*list = node;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

int		check_type(const char *str)
{
	if (*str == '|')
		return (PIPE);
	else if (*str == '<' || *str == '>')
		return (REDIRECTION);
	return (WORD);
}

int		is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

size_t	ft_strlen(char const *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*addr;

	addr = (char *)malloc(sizeof(char) \
		* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (addr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		addr[i++] = *s1++;
	while (*s2)
		addr[i++] = *s2++;
	addr[i] = '\0';
	return (addr);
}

size_t	get_dollar_len(char const *line)
{
	size_t	index;

	index = 1;
	if (!line[index])
		return (1);
	if (line[index] == '?')
		return (2);
	if (line[index] == '$')
		return (2);
	while (line[index])
	{
		if (is_quote(line[index + 1]) || is_space(line[index + 1]))
			return (index);
		index++;
	}
	return (index - 1);
}

size_t	get_dollar_index(char const *line)
{
	size_t	index;
	char	quote_flag;

	index = 0;
	quote_flag = '\0';
	while (line[index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		if (quote_flag != '\'' && line[index] == '$')
			return (index);
		index++;
	}
	return (index);
}

char	check_dollar(char c, int *flag)
{
	return (0);
}

#define SINGLE_QUOTE \'
size_t	double_array_size(char const *line, char dollar)
{
	size_t	index;
	size_t	size;
	int		quote_flag;
	int		dollar_flag;

	quote_flag = 0;
	dollar_flag = 1;
	size = 0;
	index = -1;
	while (line[++index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		if (line[index] == '$' && quote_flag != '\'')
		{
			++size;
			dollar_flag = 1;
			index += get_dollar_len(&line[index]);
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			++size;
		}
	}
	return (size);
}



void	duplicate_str(char **result, char *line)
{	
	size_t	s_index;
	size_t	index;
	size_t	r_index;
	char	quote_flag;
	int		dollar_flag;

	s_index = 0;
	r_index = 0;
	index = 0;
	dollar_flag = 1;
	if (*line == '$')
		dollar_flag = 0;
	while (line[index])
	{
		quote_flag = check_quote(*line, quote_flag);
		if (!dollar_flag && (quote_flag != '\'' && line[index] == '$'))
		{
			dollar_flag = 1;
			s_index = index;
			index += get_dollar_len(&line[index]);
			printf("%lu %lu\n", s_index, index);
			result[r_index++] = ft_strndup(&line[s_index], index - s_index);
		}
		else if (dollar_flag)
		{
			dollar_flag = 0;
			s_index = index;
			index += get_dollar_index(&line[index]);
			result[r_index++] = ft_strndup(&line[s_index], index - s_index);
		}
	}
}

char	**split_dollar(char const *line, size_t size)
{
	char	*temp;
	char	**result;
	size_t	r_size;

	temp = ft_strndup(line, size);
	r_size = double_array_size(temp, '$');
	result = (char **)malloc(sizeof(char *) * (r_size + 1));
	duplicate_str(result, temp);
	printf("size: %lu\n", r_size);
	result[r_size] = NULL;
	int index = 0;
	while (result[index])
	{
		printf("%s\n", result[index]);
		index++;
	}
	free(temp);
	return (result);
}

void	get_token(char const *line, size_t size, t_list **list)
{
	t_list	*node;
	char	*temp;
	char	**te;
	char	*content;
	int		type;
	
	te = split_dollar(line, size);
	/*
	printf("before: %s\n", line);
	content = convert_dollar(line, size);
	content = remove_quote(line, size);
	printf("after: %s\n", content);
	type = check_type(content);
	node = create_element(type, content);
	lst_addback(list, node);
	*/
}

static t_list	*create_element(int type, char *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	elem->type = type;
	elem->content = content;
	return (elem);
}
