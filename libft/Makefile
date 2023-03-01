# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 20:35:22 by chajung           #+#    #+#              #
#    Updated: 2023/03/01 19:01:53 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

TOPTARGET 	= all clean fclean re

NAME		= utils.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar
RCS			= rcs
RMFLAGS		= -r

SUB_DIR		:= ft_printf/ get_next_line/ libft/
SUB_LIB		:= ft_printf/libftprintf.a \
			   get_next_line/libftgnl.a \
			   libft/libft.a

ifeq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS), '' all))
$(TOPTARGET): $(SUB_DIR)
	@$(MAKE) merge
else
$(TOPTARGET): $(SUB_DIR)
endif

$(SUB_DIR) :
	@$(MAKE) -C $@ $(MAKECMDGOALS)

ffclean :
	@$(RM) $(NAME)
	@echo "utils fclean done"

rre :
	$(MAKE) fclean
	$(MAKE) all

merge :
	@libtool -static -o $(NAME) $(SUB_LIB)

.PHONY: $(TOPTARGET) $(SUB_DIR)
