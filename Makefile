# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 18:51:28 by agrimald          #+#    #+#              #
#    Updated: 2023/11/07 21:37:14 by agrimald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

LIBFT = include/libft/libft.a
SRCDIR = src
OBJDIR = obj

SRC = src/main.c src/utils/env.c src/signals/signals.c src/parse/check_errors.c \
	  src/lexer/tokens_lexer.c src/commands/echo.c src/commands/pwd.c

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c))

#OLD_MAKE = /usr/bin/make3.81 #make

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@printf "Compiling objects\n"
			@mkdir -p $(@D)
			@gcc $(CFLAGS) -Iinclude/libft -c $< -o $@

$(NAME): $(OBJECTS) $(LIBFT) Makefile
			@mkdir -p $(@D)
			@gcc $(CFLAGS) -o $@ $(OBJECTS) -Linclude/libft -lft
			@printf "\nCompiled successfully!\n"

fclean: clean
		@rm -rf $(NAME)

clean:
		@rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
