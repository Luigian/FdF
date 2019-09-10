# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lusanche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 10:41:38 by lusanche          #+#    #+#              #
#    Updated: 2019/08/30 21:34:49 by lusanche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEAD = includes/libft.h
SRCS = *.c
OBJS = *.o

$(NAME):
	@gcc -c -Wall -Wextra -Werror $(SRCS) -I $(HEAD)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "[INFO] Library [$(NAME)] created"

.PHONY: all, clean, fclean, re

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "[INFO] Libft Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] Library [$(NAME)] removed"

re: fclean all
