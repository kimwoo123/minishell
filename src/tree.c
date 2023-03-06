#include "../inc/minishell.h"

void	get_token(const char *line, size_t size, t_node *node)
{
	t_node	*temp;
	t_node	*new;

	new = create_node(1, ft_strndup(line, size));
	temp = node;
	while (temp->left_child)
	{
		temp = temp->left_child;
	}
	temp->left_child = new;
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
