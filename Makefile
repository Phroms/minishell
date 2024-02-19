# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 18:51:28 by agrimald          #+#    #+#              #
#    Updated: 2024/02/12 16:06:36 by ojimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

INCS = -I./include/ -I./include/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./include/Libft -lft
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline
SRCDIR = src/
OBJDIR = obj/

SRC_L = main.c utils/destroy.c \
		commands/echo.c commands/pwd.c commands/cd.c commands/exit.c \
		commands/env.c commands/export_utils.c commands/export_utils2.c \
		commands/export.c commands/unset.c  \
	   	parser/check_errors.c parser/token_analysis.c parser/tokens_operations.c \
		parser/token_manager.c parser/parser.c parser/procesos.c \
		expander/expander.c expander/split_to_expand.c expander/utils_exp.c expander/var_expander.c \
		executor/executor.c executor/heredoc.c executor/exec_execute.c executor/exec_redirections.c \
		executor/exec_utils.c executor/our_commands.c executor/exec_fds.c \
		signals/signals.c

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

#OLD_MAKE = /usr/bin/make3.81 #make

all: $(NAME)

$(OBJDIR)%.o: %.c
			@printf "Compiling objects\n"
			@mkdir -p $(@D)
			@gcc $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJECTS) Makefile include/minishell.h
			@mkdir -p $(@D)
			@gcc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
			@printf "\nCompiled successfully!\n"

fclean: clean
		@rm -rf $(NAME)

clean:
		@rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
