# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 15:10:16 by ybouddou          #+#    #+#              #
#    Updated: 2020/10/15 09:19:23 by ybouddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c\
	  get_next_line_utils.c\
	  func.c\
	  map_parsing.c\
	  

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc main.c libft/libft.a $(OBJ) mlx/libmlx.a -lz -framework OpenGL -framework AppKit -I mlx

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ) main.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

