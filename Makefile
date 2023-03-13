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

__LDFLAGS	= -L ~/.brew/opt/readline/lib
__CPPFLAGS	= -I ~/.brew/opt/readline/include

LIB			= libft/libft.a
LIB_DIR		= libft

BUILTIN		= builtin
_BUILTIN	= echo.c \
			  cd.c cd_utils0.c cd_utils1.c \
			  export.c export_utils0.c export_utils1.c \
			  pwd.c exit.c env.c unset.c

PARSE		= parse
_PARSE		= deli_parse.c dollar.c free.c tree.c

SRC_DIR		= src
OBJ_DIR		= obj
_OBJ_DIR	= builtin
__OBJ_DIR	= parse
 
SRC			= main.c utils0.c  signals.c heredoc.c pipe.c init.c envp_utils.c \
			  $(addprefix $(BUILTIN)/, $(_BUILTIN)) \
			  $(addprefix $(PARSE)/, $(_PARSE))

SRC_BONUS	= main.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ))

ifeq ($(MAKECMDGOALS), bonus)
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_BONUS))
OBJ			= $(SRC_BONUS:.c=.o)
else
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC)) \
			  $(addprefix $(SRC_DIR)/$(BUILTIN)/, $(_BUILTIN)) \
			  $(addprefix $(SRC_DIR)/$(PARSE)/, $(_PARSE))
OBJ			= $(SRC:.c=.o)
endif

ifeq ($(MAKECMDGOALS), debug)
$(NAME): $(OBJS) $(LIB)
	@$(CC) -g $(LIB) $^ -o $@ $(RLFLAGS) $(__LDFLAGS) $(__CPPFLAGS)
	@echo "minishell make done"
else
$(NAME): $(OBJS) $(LIB)
	@$(CC) $(LIB) $^ -o $@ $(RLFLAGS) $(__LDFLAGS) $(__CPPFLAGS)
	@echo "minishell make done"
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@ $(__CPPFLAGS)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

# $(NAME): $(OBJS) $(LIB)
# 	$(CC) $(CFLAGS) $(LIB) $^ -o $@

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(_OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/$(_OBJ_DIR)

$(__OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/$(__OBJ_DIR)

all: $(OBJ_DIR) $(_OBJ_DIR) $(__OBJ_DIR) $(NAME)

bonus: $(OBJ_DIR) $(_OBJ_DIR) $(__OBJ_DIR) $(NAME)

debug: $(OBJ_DIR) $(_OBJ_DIR) $(__OBJ_DIR) $(NAME)

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
