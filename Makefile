# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 18:51:28 by agrimald          #+#    #+#              #
#    Updated: 2023/11/14 17:18:01 by agrimald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

INCS = -I./include/ -I./include/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./include/Libft -lft
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline 
SRCDIR = src/
OBJDIR = obj/

SRC_L = main.c utils/env.c signals/signals.c commands/echo.c commands/pwd.c \
		lexer/tokens_lexer.c parser/check_errors.c parser/token_manager.c 

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

#OLD_MAKE = /usr/bin/make3.81 #make

all: $(NAME)

$(OBJDIR)%.o: %.c
			@printf "Compiling objects\n"
			@mkdir -p $(@D)
			@gcc $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJECTS) Makefile
			@mkdir -p $(@D)
			@gcc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
			@printf "\nCompiled successfully!\n"

fclean: clean
		@rm -rf $(NAME)

clean:
		@rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
