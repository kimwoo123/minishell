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

include inc/flag_mkfile
include inc/var_mkfile

ifeq ($(MAKECMDGOALS), bonus)	
include inc/bns_mkfile
else
include inc/var_mkfile
endif

ifeq ($(MAKECMDGOALS), bonus)
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)

$(OBJ_B_DIR):
	@mkdir -p $(OBJ_B_DIR)
else
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
endif

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

all: $(OBJ_DIR) $(NAME)
	$(RM) $(RMFLAGS) $(OBJ_B_DIR)

bonus: $(OBJ_B_DIR) $(NAME)
	$(RM) $(RMFLAGS) $(OBJ_DIR)

# debug: $(OBJ_DIR) $(NAME)

clean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "minishell clean done"

fclean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(RM) $(RMFLAGS) $(NAME)
	@echo "minishell fclean done"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus
