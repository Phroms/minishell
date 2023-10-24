NAME = minishell
CFLAGS = -Wall -Wextra -Werror -MMD -fsanitize=address
FILES = main/main.c \
		parser/lexer.c parser/separadors.c parser/create_process.c parser/utils.c \
		parser/utils2.c parser/expansor.c parser/create_redi.c \
		checker/errors.c checker/checker.c \
		execution/executor2.c builtins/echo.c builtins/env.c builtins/exit.c \
		execution/executor.c execution/finds.c execution/utils_executor.c execution/redi.c
		
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(FILES))
CC = cc

OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(FILES:.c=.d))
RM = rm -rf
LIB = lib/libft/libft.a lib/readline/libreadline.a lib/readline/libhistory.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 -I./ -I lib/readline -c $< -o $@

all:
	@$(MAKE) -C lib/libft --no-print-directory
	@if ! [ -f lib/readline/libreadline.a ]; then \
		cd ./lib/readline/ &> /dev/null && ./configure &> /dev/null && \
		$(MAKE) --no-print-directory &> /dev/null; \
	fi
	@$(MAKE) $(NAME) --no-print-directory

$(NAME):: $(OBJS)
	@$(CC) -ltermcap $(CFLAGS) $(OBJS) $(LIB) -o $@

$(NAME)::
	@echo -n

clean:
	@$(RM) $(OBJ_DIR) --no-print-directory
	@$(MAKE) clean -C lib/libft --no-print-directory 
	@$(MAKE) clean -C lib/readline --no-print-directory &> /dev/null

fclean: clean
	@$(RM) $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)
