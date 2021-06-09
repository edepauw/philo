# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edepauw <edepauw@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 14:41:35 by tgrangeo          #+#    #+#              #
#    Updated: 2021/06/08 11:08:42 by edepauw          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


HEADER =	libft.h

SRCS =		ft_strlen.c ft_atoi.c

OBJS	=	${SRCS:.c=.o}

NAME	=	libft.a

RM		=	rm -f

FLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@
$(NAME): $(OBJS) $(HEADER)
	ar rcs $(NAME) $(OBJS) 
bonus:		$(OBJS) $(HEADER)
	ar rcs $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)
fclean:	clean
	$(RM) $(NAME)
re: 	fclean all