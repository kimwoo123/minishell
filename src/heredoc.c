/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:01:06 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 10:31:34 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*expand_str_hd(t_data *data, const char *line)
{
	char	**temp;
	char	*result;

	temp = split_dollar_hd(line);
	result = convert_dollar(temp, data);
	free_double(temp);
	return (result);
}

static void	join_free1(char **str_nl, char **temp)
{
	*str_nl = ft_strjoin(*temp, "\n");
	if (*str_nl == NULL)
		exit_with_str("malloc error in preprocess", EXIT_FAILURE);
	free(*temp);
}

static void	join_free2(char **str, char **str_nl, char **expand)
{
	char	*temp;

	temp = *str;
	*str = ft_strjoin(temp, *expand);
	if (*str == NULL)
		exit_with_str("malloc error in preprocess", EXIT_FAILURE);
	free(temp);
	free(*expand);
	free(*str_nl);
}

static int	rl_heredoc(t_data *data, t_list **list)
{	
	char	*str;
	char	*str_nl;
	char	*expand;
	char	*temp;

	str = ft_strdup("");
	if (str == NULL)
		return (FAILURE);
	while (1)
	{
		temp = readline("> ");
		if (temp == NULL)
			break ;
		if (is_equal_to(temp, (*list)->content) == TRUE)
		{
			free(temp);
			break ;
		}
		join_free1(&str_nl, &temp);
		expand = expand_str_hd(data, str_nl);
		join_free2(&str, &str_nl, &expand);
	}
	free((*list)->content);
	(*list)->content = str;
	return (SUCCESS);
}

void	preprocess_heredoc(t_data *data, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
	{
		if (temp->type == REDIR_TOKEN && is_equal_to(temp->content, "<<"))
		{
			temp = temp->next;
			if (rl_heredoc(data, &(temp)) == FAILURE)
				exit_with_str("malloc error in preprocess", EXIT_FAILURE);
		}
		temp = temp->next;
	}
}
