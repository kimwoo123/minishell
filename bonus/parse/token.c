/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:42:40 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/28 10:46:40 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	check_type(const char *str)
{
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2))
		return (OPERATOR);
	else if (*str == '(')
		return (SUBS_OPEN);
	else if (*str == ')')
		return (SUBS_CLOSE);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '<' || *str == '>')
		return (REDIR_TOKEN);
	return (WORD);
}

char	*remove_quote(const char *line)
{
	char	quote_flag;
	char	*result;
	size_t	index;
	size_t	r_index;

	result = (char *)malloc(ft_strlen(line) + 1);
	if (result == NULL)
		return (NULL);
	quote_flag = '\0';
	index = 0;
	r_index = 0;
	while (line[index])
	{
		if (!quote_flag && is_quote(line[index]))
			quote_flag = line[index];
		else if (quote_flag == line[index])
			quote_flag = '\0';
		else
			result[r_index++] = line[index];
		++index;
	}
	result[r_index] = '\0';
	return (result);
}

void	get_token(const char *line, size_t size, t_list **list, int type)
{
	t_list	*node;
	char	*temp;
	char	*content;
	size_t	index;

	index = trim_line(line);
	temp = ft_strndup(&line[index], size - index);
	content = remove_quote(temp);
	free(temp);
	if (content == NULL)
		exit_with_str("malloc error in get_token", EXIT_FAILURE);
	node = create_element(type, content);
	if (node == NULL)
		exit_with_str("malloc error in create_element", EXIT_FAILURE);
	lst_addback(list, node);
}

void	expand_space_split(const char *line, t_list **list, int type)
{
	size_t	index;
	size_t	start_index;
	char	quote_flag;
	int		space_flag;

	start_index = 0;
	space_flag = 0;
	quote_flag = '\0';
	index = 0;
	while (line[index])
	{
		quote_flag = check_quote(line[index], quote_flag);
		if (!quote_flag && (space_flag && is_space(line[index])))
		{
			get_token(&line[start_index], index - start_index, list, type);
			start_index = index;
			space_flag = 0;
		}
		else if (!quote_flag && (!space_flag && !is_space(line[index])))
			space_flag = 1;
		++index;
	}
	if (space_flag)
		get_token(&line[start_index], index - start_index, list, type);
}

void	tokenize(const char *line, size_t size, t_list **list, t_data *data)
{
	char	*expansion;
	size_t	index;
	int		type;

	type = check_type(line);
	expansion = expand_str(line, size, data);
	index = trim_line(expansion);
	expand_space_split(&expansion[index], list, type);
	free(expansion);
}
