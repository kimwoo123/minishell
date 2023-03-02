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
RLFLAGS		= -lreadline
RMFLAGS		= -r

LIB			= libft/libft.a
LIB_DIR		= libft

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= main.c utils0.c echo.c cd.c pwd.c exit.c
SRC_BONUS	= main.c utils0.c echo.c cd.c pwd.c exit.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ))

ifeq ($(MAKECMDGOALS), bonus)
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
OBJ			= $(SRC_BONUS:.c=.o)
else
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ			= $(SRC:.c=.o)
endif

ifeq ($(MAKECMDGOALS), debug)
$(NAME): $(OBJS) $(LIB)
	@$(CC) -g $(LIB) $^ -o $@ $(RLFLAGS)
	@echo "minishell make done"
else
$(NAME): $(OBJS) $(LIB)
	@$(CC) $(LIB) $^ -o $@ $(RLFLAGS)
	@echo "minishell make done"
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

# $(NAME): $(OBJS) $(LIB)
# 	$(CC) $(CFLAGS) $(LIB) $^ -o $@

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_DIR) $(NAME)

debug: $(OBJ_DIR) $(NAME)

clean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "minishell clean done"

fclean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(RM) $(RMFLAGS) $(NAME)
	@echo "minishell fclean done"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus
