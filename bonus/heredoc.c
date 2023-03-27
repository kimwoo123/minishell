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

int	test_heredoc(t_data *data, t_list **list)
{	
	char	*delim;
	char	*expand;
	char	*save;
	char	*temp;

	save = ft_strdup("");
	if (save == NULL)
		return (FAILURE);
	delim = ft_strjoin((*list)->content, "\n");
	if (delim == NULL)
		return (FAILURE);
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		temp = get_next_line(STDIN_FILENO);
		if (temp == NULL)
			break ;
		if (is_equal_to(temp, delim) == TRUE)
			break ;
		expand = expand_str_hd(data, temp);
		free(temp);
		temp = save;
		save = ft_strjoin(temp, expand);
		if (save == NULL)
			return (FAILURE);
		free(temp);
		free(expand);
	}
	free((*list)->content);
	(*list)->content = save;
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
			test_heredoc(data, &(temp));
		}
		temp = temp->next;
	}
}
