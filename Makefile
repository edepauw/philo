# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:04:45 by tgrangeo          #+#    #+#              #
#    Updated: 2021/04/28 14:36:45 by edepauw          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/philo_one.c srcs/routine.c srcs/philo_utils.c srcs/philo_utils1.c

NAME = philo_one.a
NAME_EXEC = philo_one
HEADER = 
FLAGS = -Werror -Wall -Wextra
LIBFT = libft/libft.a
RM = rm -rf
OBJS = ${SRCS:.c=.o}

all: $(LIBFT) $(NAME)
	gcc $(FLAGS) $(NAME) $(LIBFT) -o $(NAME_EXEC)

%.o : %.c $(LIBFT) $(HEADER)
	gcc $(FLAGS) -c $< -o $@

$(NAME):$(OBJS) $(HEADER)
	cp $(LIBFT) ./$(NAME)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	cd libft/ && $(MAKE)

clean:
	$(RM) $(OBJS)
	cd libft/ && $(MAKE) fclean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_EXEC)

re: fclean all

