# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:04:45 by tgrangeo          #+#    #+#              #
#    Updated: 2021/02/23 11:06:45 by edepauw          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS = philo_one.c

NAME = philo_one.a
NAME_EXEC = philo_one
HEADER = 
FLAGS = #-Werror -Wall -Wextra
#ifdef DEBUG
#FLAGS += -g3
#endif
LIBFT = libft/libft.a
RM = rm -rf
OBJS = ${SRCS:.c=.o}

all: $(LIBFT) $(NAME)
	gcc $(FLAGS) $(NAME)	$(LIBFT) -o $(NAME_EXEC)

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

