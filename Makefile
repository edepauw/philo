# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:20:09 by edepauw           #+#    #+#              #
#    Updated: 2021/06/08 11:09:44 by edepauw          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME1	= philo_one
NAME2	= philo_two
NAME3	= philo_three

CFLAGS 	= -Wall -Wextra -Werror

SRC1 	= philo_one.c philo_utils.c philo_utils1.c routine.c
SRC2 	= philo_two.c philo_utils.c philo_utils1.c routine.c
SRC3 	= philo_three.c philo_utils.c philo_utils1.c routine.c

.PHONY: all clean fclean re

RED		=	\033[0;31m
GREEN	=	\033[0;32m
NC		=	\033[0m

OBJSFD1 	= philo_one_dir
OBJSFD2 	= philo_two_dir
OBJSFD3 	= philo_three_dir


OBJS1 	= $(addprefix $(OBJSFD1)/,$(SRC1:.c=.o))
OBJS2 	= $(addprefix $(OBJSFD2)/,$(SRC2:.c=.o))
OBJS3 	= $(addprefix $(OBJSFD3)/,$(SRC3:.c=.o))

LIBFT_HDR 	= -I./libft
LIB_BINARY	= -L./libft -lft
LIBFT		= libft/libft.a

$(LIBFT):
	@make -C libft re

all: $(LIBFT) $(NAME1) $(NAME2) $(NAME3)

%.o: %.c
	@$(CC) $(CFLAGS) $(HDR) $(LIBFT_HDR) -c $< -o $@

$(NAME1): $(OBJS1) $(LIBFT)
	@echo "$(GREEN)compiling $@...$(NC)"
	gcc $(CFLAGS) $(OBJS1) $(LIB_BINARY) -o $@
	@echo "$(GREEN)$@ is ready to test$(NC)"

$(NAME2): $(OBJS2) $(LIBFT)
	@echo "$(GREEN)compiling $@...$(NC)"
	@gcc $(CFLAGS) $(OBJS2) $(LIB_BINARY) -o $@
	@echo "$(GREEN)$@ is ready to test$(NC)"

$(NAME3): $(OBJS3) $(LIBFT)
	@echo "$(GREEN)compiling $@...$(NC)"
	@gcc $(CFLAGS) $(OBJS3) $(LIB_BINARY) -o $@
	@echo "$(GREEN)$@ is ready to test$(NC)"

clean:
	@echo "$(RED)deleting object files...$(NC)"
	@/bin/rm -f $(OBJS2)
	@/bin/rm -f $(OBJS1)
	@/bin/rm -f $(OBJS3)
	@make -C ./libft clean

fclean: clean
	@echo "$(RED)deleting both executables...$(NC)"
	@/bin/rm -f $(NAME1)
	@/bin/rm -f $(NAME2)
	@/bin/rm -f $(NAME3)
	@make -C ./libft fclean

re: fclean all