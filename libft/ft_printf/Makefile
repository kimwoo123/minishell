# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 16:22:46 by wooseoki          #+#    #+#              #
#    Updated: 2023/03/01 15:45:25 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rc
RM = rm
RMFLAGS = -rf
SRC = ft_printf_bonus.c parce_bonus.c util_bonus.c \
	  convert_c_bonus.c convert_i_bonus.c convert_p_bonus.c \
	  convert_s_bonus.c convert_u_bonus.c convert_x_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_DIR = obj/
SRC_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(OBJ_DIR) $(NAME)
	
clean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR) 
	@echo "ft_printf clean done"

fclean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(NAME)
	@echo "ft_printf fclean done"

re :
	$(MAKE) clean
	$(MAKE) all

$(NAME) : $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "ft_printf make done"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
