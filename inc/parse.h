/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:29:40 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/22 10:37:50 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include "structure.h"

/* lexer */
void	seperate_meta(const char *line, size_t size, t_list **list, t_data *d);
void	split_space(const char *line, size_t size, t_list **list, t_data *data);
int		repeat_meta(const char *line, size_t index);
void	split_delimiter(const char *line, t_list **list, t_data *data);
t_list	*scan_command(const char *line, t_data *data);

/* parse_utils */
char	check_quote(char c, char flag);
int		is_delimiter(char c);
size_t	trim_line(const char *line);
int		close_quote(const char *line);

/* utils */
char	*ft_strndup(const char *begin, size_t size);
int		is_space(char c);
int		is_quote(char c);

/* token */
t_list	*create_element(int type, char *content);
void	get_token(const char *line, size_t size, t_list **t_list, t_data *d);
int		check_type(const char *str);
void	lst_addback(t_list **list, t_list *node);
char	*remove_quote(const char *line);

/* split_dollar */
size_t	get_dollar_len(const char *line);
size_t	get_dollar_index(const char *line, char *quote_flag);
size_t	double_array_size(const char *line, char *quote_flag);
void	duplicate_str(char **result, const char *line, char *quote_flag);
char	**split_dollar(const char *line, size_t size);

/* expand_str */
char	*convert_variable(char *str, t_data *data);
char	*merge_str(char **split_str);
char	*expand_str(const char *line, size_t size, t_data *data);
char	*convert_dollar(char **str, t_data *data);

/* free */
void	free_list(t_list **list);
void	free_double(char **str);
void	free_stack_table(t_stack *stack, t_fptr **table);
void	free_tree(t_tree *node);

/* syntax */
int		check_syntax(t_list **token_list);
int		repeat_reduce_shift(t_fptr **reduce_table, t_stack **stack);
int		reduce_token(t_fptr **reduce_table, t_stack **stack_node);
int		shift_token(t_fptr **reduce_table, t_stack **stack_node);
int		parse_token(t_list **token_list);

/* stack */
t_stack	*create_elem(int type);
int		pop_stack(t_stack **stack);
void	push_stack(t_stack **stack, int type);

/* reduce_rule */
int		reduce_redirection(t_stack **stack_node);
int		reduce_cmd_token(t_stack **stack_node);
int		reduce_command(t_stack **stack_node);
int		reduce_pipe_command(t_stack **stack_node);
int		reduce_group_command(t_stack **stack_node);

/* shift_rule */
int		shift_command(t_stack **stack_node);
int		shift_r_command(t_stack **stack_node);
int		shift_ct_command(t_stack **stack_node);
int		shift_w_ct(t_stack **stack_node);

/* set_table */
void	set_reduce_function(t_fptr **reduce_table);
t_fptr	**init_parse_table(void);

#endif
