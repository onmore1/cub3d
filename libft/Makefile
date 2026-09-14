# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 13:48:10 by vananiev          #+#    #+#              #
#    Updated: 2025/09/02 12:04:51 by vananiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = libft.a
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
 ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
 ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
 ft_putstr_fd.c ft_split.c ft_strchr.c ft_striteri.c ft_strlcat.c \
 ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
 ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strjoin.c ft_strdup.c \
 printf/ft_printf.c printf/ft_utils.c printf/hex_helper.c \
 get_next_line/get_next_line_utils.c get_next_line/get_next_line.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./printf -I./get_next_line
AR = ar rc


all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
