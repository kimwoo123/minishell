# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 17:15:30 by chajung           #+#    #+#              #
#    Updated: 2023/03/26 11:43:43 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

# ----------------------
PAR_SRC		:= \
		set_table.c shift_rule.c reduce_rule.c syntax.c \
		stack.c free.c expand_str.c split_dollar.c \
		token.c utils.c parse_utils.c lexer.c reduce_rule2.c \
		parse.c
PAR_DIR		:= bonus/parse
PAR_OBJ_DIR	:= obj/parse
PAR_OBJ		:= $(PAR_SRC:.c=.o)
PAR_OBJS	:= $(addprefix $(PAR_OBJ_DIR)/, $(PAR_OBJ))
PAR_SRCS	:= $(addprefix $(PAR_DIR)/, $(PAR_SRC))


BTI_DIR		:= bonus/builtin
BTI_SRC		:= \
			echo.c  pwd.c exit.c env.c  export_utils1.c unset.c \
			export.c export_utils0.c \
			cd.c cd_utils0.c cd_utils1.c cd_utils2.c
BTI_OBJ_DIR := obj/builtin
BTI_OBJS	:= $(addprefix $(BTI_OBJ_DIR)/, $(BTI_OBJ))
BTI_OBJ		:= $(BTI_SRC:.c=.o)
BTI_SRCS	:= $(addprefix $(BTI_DIR)/, $(BTI_SRC))


COM_DIR		:= bonus
COM_SRC		:= \
			main.c run.c utils0.c utils1.c signals.c heredoc.c heredoc_utils.c \
			init.c envp_utils.c tree.c tree_utils0.c tree_utils1.c redir.c redir_utils.c \
			fork.c command.c command_utils.c wildcard.c
COM_OBJ_DIR := obj
COM_OBJS	:= $(addprefix $(COM_OBJ_DIR)/, $(COM_OBJ))
COM_OBJ		:= $(COM_SRC:.c=.o)
COM_SRCS	:= $(addprefix $(COM_DIR)/, $(COM_SRC))


$(COM_OBJ_DIR)/%.o : $(COM_DIR)/%.c | $(COM_OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(BTI_OBJ_DIR)/%.o : $(BTI_DIR)/%.c | $(BTI_OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(PAR_OBJ_DIR)/%.o : $(PAR_DIR)/%.c | $(PAR_OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)



# ----------------------
NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RLFLAGS		= -lreadline
RMFLAGS		= -r

LDFLAGS		= -L ~/.brew/opt/readline/lib
CPPFLAGS	= -I ~/.brew/opt/readline/include -I inc

LIB			= libft/libft.a
LIB_DIR		= libft

ALL_SRCS	= $(COM_SRCS) $(BTI_SRCS) $(PAR_SRCS)
ALL_OBJS	= $(COM_OBJS) $(BTI_OBJS) $(PAR_OBJS)

OBJ_DIR		:= obj obj/builtin obj/parse
SRC_DIR		:= src src/builtin src/parse

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ---------------------------

$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

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

