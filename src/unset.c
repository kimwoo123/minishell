
#include "../inc/minishell.h"

static int	check_same_key(char *str, char *key)
{
	if (!ft_strncmp(str, key, ft_strlen_before_equal_sign(key)))
	{
		if (ft_strlen_before_equal_sign(str) == ft_strlen_before_equal_sign(key))
			return (FOUND);
	}
	return (NOT_FOUND);
}

static char	**delete_environment_variable(char **array, char *key)
{
	char	**new_array;
	size_t	size;
	size_t	i;
	size_t	j;

	size = get_size_double_array(array);
	new_array = (char **)malloc(sizeof(char *) * size);
	if (!new_array)
		return (NULL);
	i = 0;
	j = 0;
	while (array[i])
	{
		if (check_same_key(array[i], key) == FOUND)
			i++;
		else
		{
			new_array[j] = ft_strdup(array[i]);
			if (!new_array[j])
				return (NULL);
			i++;
			j++;
		}
	}
	new_array[j] = NULL;
	return (new_array);
}

int	unset_command(t_data *data)
{
	size_t	index;
	char	**array;

	index = 1;
	while (data->commands[index])
	{
		if (ft_getenv(data->copied_envp, data->commands[index]) == KEY_AND_VALUE \
		|| ft_getenv(data->copied_envp, data->commands[index]) == ONLY_KEY)
		{
			array = delete_environment_variable(data->copied_envp, data->commands[index]);
			if (!array)
				ft_perror("unset_command error", EXIT_FAILURE);
			free_double_array(data->copied_envp);
			data->copied_envp = array;
		}
		index++;
	}
	return (0);
}
