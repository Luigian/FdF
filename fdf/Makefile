# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lusanche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/11 12:23:10 by lusanche          #+#    #+#              #
#    Updated: 2019/09/10 02:58:09 by lusanche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS = *.c
OBJS = *.o
LIBFT_DIR = libft/
MINILIBX_DIR =  minilibx_macos/
FRAMES = -framework OpenGL -framework AppKit

$(NAME):
	@make -C $(LIBFT_DIR) fclean && make -C $(LIBFT_DIR)
	@make -C $(MINILIBX_DIR) clean && make -C $(MINILIBX_DIR)
	@$(CC) -c $(FLAGS) $(SRCS) -I $(LIBFT_DIR) -I $(MINILIBX_DIR) 
	@$(CC) -o $(NAME) $(OBJS) -I $(LIBFT_DIR) -I $(MINILIBX_DIR)\
		-L $(LIBFT_DIR) -lft -L $(MINILIBX_DIR) -lmlx $(FRAMES)	
	@echo "[INFO] Binary [$(NAME)] created"

.PHONY: all, clean, fclean, re

all: $(NAME)

clean:
	@make -C $(LIBFT_DIR) fclean 
	@make -C $(MINILIBX_DIR) clean 
	@rm -f $(OBJS)
	@echo "[INFO] Fdf Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] Binary [$(NAME)] removed"

re: fclean all
