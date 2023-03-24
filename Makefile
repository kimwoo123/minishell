# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 17:15:30 by chajung           #+#    #+#              #
#    Updated: 2023/03/23 18:38:40 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

ifeq ($(MAKECMDGOALS), bonus)	
include inc/bns_mkfile
else
include inc/var_mkfile
endif

include inc/flag_mkfile

ifeq ($(MAKECMDGOALS), debug)
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) -g $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)
else
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)
endif

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

all: $(OBJ_DIR) $(NAME)
	@echo "minishell make done"

bonus: $(OBJ_DIR) $(NAME)
	@echo "minishell make bonus done"

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
