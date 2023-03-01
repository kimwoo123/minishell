# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 17:15:30 by chajung           #+#    #+#              #
#    Updated: 2023/03/01 17:15:33 by chajung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RMFLAGS		= -r

LIB			= libft/utils.a
LIB_DIR		= libft

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= main.c 
SRC_BONUS	= main.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ))

ifeq ($(MAKECMDGOALS), bonus)
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
OBJ			= $(SRC_BONUS:.c=.o)
else
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ			= $(SRC:.c=.o)
endif

$(NAME): $(OBJS) $(LIB)
	$(CC) $(LIB) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

# $(NAME): $(OBJS) $(LIB)
# 	$(CC) $(CFLAGS) $(LIB) $^ -o $@

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_DIR) $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(MAKE) fclean -C $(LIB_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
