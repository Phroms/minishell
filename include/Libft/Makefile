# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 19:07:28 by agrimald          #+#    #+#              #
#    Updated: 2023/11/14 17:42:06 by agrimald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nombre del programa
NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
AR = ar rc
LIB = libft.h

SOURCES_DIR = bools libft_fd strings memory lists get_next_line ft_printf

BOOLS_SRC = ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c ft_isprint.c

STRINGS_SRC = ft_strlen.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strncmp.c \
			  ft_strnstr.c ft_atoi.c ft_strdup.c ft_atoi.c ft_strchr.c \
			  ft_strrchr.c ft_strlcat.c ft_substr.c ft_strjoin.c \
			  ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c ft_strmapi.c \
			  ft_strcmp.c

MEMORY_SRC = ft_bzero.c ft_calloc.c ft_memcpy.c ft_memcpy.c ft_memchr.c \
			 ft_memcmp.c ft_memset.c ft_memmove.c ft_realloc.c

LIBFT_FD_SRC = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

LISTS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c

GET_NEXT_LINE_SRC = get_next_line.c get_next_line_utils.c

FT_PRINTF_SRC = ft_print_char.c ft_print_hexa.c ft_print_number.c \
			ft_print_pointer.c ft_printf.c

SOURCES = $(addprefix bools/, $(BOOLS_SRC)) \
		  		$(addprefix strings/, $(STRINGS_SRC)) \
				$(addprefix memory/, $(MEMORY_SRC)) \
				$(addprefix libft_fd/, $(LIBFT_FD_SRC)) \
				$(addprefix lists/, $(LISTS_SRC)) \
				$(addprefix get_next_line/, $(GET_NEXT_LINE_SRC)) \
				$(addprefix ft_printf/, $(FT_PRINTF_SRC))

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

all: $(NAME)

%.o:%.c $(LIB)
		@echo "Compilando ... $@"
		$(CC) -MMD -c $(FLAGS) $< -o $@

$(NAME): $(OBJECTS) $(LIB)
		@echo "\nLinking ... $@\n"
		$(AR) ${NAME} ${OBJECTS}
		@echo "\nHecho!\n"
clean:
		@rm -rf $(OBJECTS) $(OBJECTS) $(DEPS) $(DEPS)
		@printf "removed objects (.o) & deps (.d)!\n"

fclean: clean
		@rm -rf $(NAME)
		@printf "Removed libft.a!\n"

re: fclean all

-include $(DEPS) $(DEPS)

.PHONY:	all clean fclean re
