#ifndef TREE_H
# define TREE_H
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

#define DELIMITER "<>|"

typedef struct	s_node
{
	int				type;
	char			*content;
	struct s_node	*left_child;
	struct s_node	*right_child;	
}	t_node;

typedef	struct	s_stack
{
	int				type;
	char			*content;
	struct s_stack	*next;
}	t_stack;

typedef struct	s_list
{
	int				type;
	char			*content;
	struct s_list	*next;
}	t_list;

enum	e_type
{
	PIPE,
	REDIRECTION,
	WORD,
};

int		split_delimiter(const char *line, t_list **list);
int		repeat_meta(const char *line, size_t index);
void	split_space(const char *line, size_t size, t_list **list);
void	seperate_meta(const char *line, size_t size, t_list **list);
void	get_token(const char *line, size_t size, t_list **list);
char	check_quote(char c, char flag);
char	*ft_strndup(const char *begin, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
int		is_quote(const char c);
t_node	*create_node(int type, char *content);
#endif
