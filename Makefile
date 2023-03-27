# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 17:15:30 by chajung           #+#    #+#              #
#    Updated: 2023/03/27 14:28:08 by wooseoki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

include inc/flag_mkfile

ifeq ($(MAKECMDGOALS), bonus)
include inc/bns_mkfile
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)

$(OBJ_B_DIR):
	$(RM) $(RMFLAGS) $(OBJ_DIR) $(NAME)
	@mkdir -p $(OBJ_B_DIR)
else
include inc/var_mkfile
$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(LIB) $^ -o $@ $(RLFLAGS) $(LDFLAGS) $(CPPFLAGS)

$(OBJ_DIR):
	$(RM) $(RMFLAGS) $(OBJ_B_DIR) $(NAME)
	@mkdir -p $(OBJ_DIR)
endif

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_B_DIR) $(NAME)


clean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "minishell clean done"

fclean:
	@$(RM) $(RMFLAGS) $(OBJ_DIR)
	@$(RM) $(RMFLAGS) $(OBJ_B_DIR)
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(RM) $(RMFLAGS) $(NAME) minishell.dSYM
	@echo "minishell fclean done"

re:
	@$(MAKE) fclean
	@$(MAKE) all

