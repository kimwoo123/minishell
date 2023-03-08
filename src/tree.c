#include "../inc/minishell.h"

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
	if (*str == '<' || *str == '>')
		return (REDIRECTION);
	return (WORD);
}

void	get_token(const char *line, size_t size, t_list **list)
{
	t_list	*temp;
	char	*content;
	int		type;

	content = ft_strndup(line, size);
	type = check_type(content);
	temp = create_element(type, content);
	lst_addback(list, temp);
}

t_node	*create_node(int type, char *content)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->content = content;
	node->left_child = NULL;
	node->right_child = NULL;
	return (node);
}
