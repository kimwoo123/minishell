# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 13:53:01 by wooseoki          #+#    #+#              #
#    Updated: 2023/02/27 14:32:24 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftgnl.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rc
RM = rm
RMFLAGS = -rf
SRC = get_next_line_bonus.c \
	  get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_DIR = obj/
SRC_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(OBJ_DIR) $(NAME)

clean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@echo "get_next_line clean done"

fclean :
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(NAME)
	@echo "get_next_line fclean done"

re :
	$(MAKE) clean
	$(MAKE) all

$(NAME) : $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "get_next_line make done"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
