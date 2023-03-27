# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 20:35:22 by chajung           #+#    #+#              #
#    Updated: 2023/03/08 14:14:31 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar
RCS			= rcs
RMFLAGS		= -r

SRC_DIR		= src
OBJ_DIR		= obj

SRC 		= \
			get_next_line_bonus.c get_next_line_utils_bonus.c \
			ft_memset.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_atoi.c \
			ft_strncmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
			ft_strrchr.c ft_substr.c ft_strnstr.c ft_calloc.c ft_strdup.c \
			ft_strjoin.c ft_itoa.c ft_strtrim.c ft_split.c ft_bzero.c ft_memcpy.c \
			ft_memmove.c ft_memchr.c ft_memcmp.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

OBJ 		= $(SRC:.c=.o) 
OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(RCS) $@ $^
	@echo "libft make done"

$(OBJ_DIR):
	@mkdir -p $(@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@echo "libft clean done"

fclean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(NAME)
	@echo "libft fclean done"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
