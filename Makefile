# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:20:09 by edepauw           #+#    #+#              #
#    Updated: 2021/05/03 10:33:48 by edepauw          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME1	= checker
NAME2	= push_swap

CFLAGS 	= -Wall -Wextra -Werror -g
#CFLAGS	= -g3 -fsanitize=address
SRC1 	= checker.c instruction/instruc1.c instruction/instruc2.c instruction/instruc3.c utils.c utils2.c utils3.c sort_arg.c utils4.c

SRC2 	= push_swap.c instruction/instruc1.c instruction/instruc2.c instruction/instruc3.c utils.c utils2.c utils3.c sort_arg.c algo_chunk/chunk1.c algo_chunk/big_list.c algo_chunk/chunk2.c algo_chunk/chunk3.c utils4.c algo_chunk/chunk4.c algo_chunk/chunk5.c

.PHONY: all clean fclean re

RED		=	\033[0;31m
GREEN	=	\033[0;32m
NC		=	\033[0m

OBJSFD1 	= philo_one/srcs
OBJSFD2 	= srcs
OBJSFD3 	= srcs

OBJS1 	= $(addprefix $(OBJSFD)/,$(SRC1:.c=.o))
OBJS2 	= $(addprefix $(OBJSFD)/,$(SRC2:.c=.o))

HDR 		= -I./includes
LIBFT_HDR 	= -I./libft/includes
LIB_BINARY	= -L./libft -lft
LIBFT		= libft/libft.a

$(LIBFT):
	@make -C libft re

all: $(LIBFT) $(NAME1) $(NAME2)

%.o: %.c
	@$(CC) $(CFLAGS) $(HDR) $(LIBFT_HDR) -c $< -o $@

$(NAME1): $(OBJS1) $(LIBFT)
	@echo "$(GREEN)compiling $@...$(NC)"
	@gcc $(CFLAGS) $(OBJS1) $(LIB_BINARY) -o $@
	@echo "$(GREEN)$@ is ready to test$(NC)"

$(NAME2): $(OBJS2) $(LIBFT)
	@echo "$(GREEN)compiling $@...$(NC)"
	@gcc $(CFLAGS) $(OBJS2) $(LIB_BINARY) -o $@
	@echo "$(GREEN)$@ is ready to test$(NC)"

clean:
	@echo "$(RED)deleting object files...$(NC)"
	@/bin/rm -f $(OBJS2)
	@/bin/rm -f $(OBJS1)
	@make -C ./libft clean

fclean: clean
	@echo "$(RED)deleting both executables...$(NC)"
	@/bin/rm -f $(NAME1)
	@/bin/rm -f $(NAME2)
	@make -C ./libft fclean

re: fclean all