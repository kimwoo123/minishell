# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 20:35:22 by chajung           #+#    #+#              #
#    Updated: 2022/11/21 18:43:54 by chajung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TOPTARGET 	= all clean fclean re

NAME		= utils.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar
RCS			= rcs
RMFLAGS		= -r

SUB_DIR		:= ft_printf/ get_next_line/ libft/
SUB_LIB		:= ft_printf/libftprintf.a \
			   get_next_line/get_next_line.a \
			   libft/libft.a

$(TOPTARGET): $(SUB_DIR) $(NAME)

$(SUB_DIR) :
	@$(MAKE) -C $@ $(MAKECMDGOALS)

$(NAME) :
	@libtool -static -o $(NAME) $(SUB_LIB)
	@echo "utils make done"

fclean :
	@$(RM) $(NAME)
	@echo "utils fclean done"

re :
	@$(RM) $(NAME)
	@$(MAKE) $(NAME)

.PHONY: $(TOPTARGET) $(SUB_DIR)
