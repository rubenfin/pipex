GNL = get_next_line.c get_next_line_utils.c
SRCS_BONUS = ft_split_bonus.c here_doc.c leaks.c path.c pipes.c \
pipex_bonus.c pipex_bonus_utils.c security.c setup_cmd.c \
$(GNL)
SRCS_MANDATORY = ft_split.c pipex_utils.c pipex.c leaks_man.c path_man.c

OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS_MANDATORY:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = objs

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

VPATH = mandatory bonus bonus/gnl .

INCLUDE_BONUS = -I./bonus -I./bonus/gnl
INCLUDE = -I./mandatory

BONUS = pipex_bonus
NAME = pipex

all: $(NAME)
bonus: $(BONUS)

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS): $(OBJS_DIR) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS) $(INCLUDE_BONUS)
	@echo "$(GREEN)Compiled bonus!$(DEFAULT)"

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)
	@echo "$(GREEN)Compiled mandatory!$(DEFAULT)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(YELLOW)Removed all objects!$(DEFAULT)"

fclean: clean
	@$(RM) $(BONUS)
	@$(RM) $(NAME)
	@echo "$(RED)Removed executables!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re bonus


#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m