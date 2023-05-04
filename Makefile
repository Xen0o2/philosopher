# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 10:17:25 by alecoutr          #+#    #+#              #
#    Updated: 2023/05/03 18:10:18 by alecoutr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	=   philo.c \

OBJS	= $(SRCS:.c=.o)

GCC		= gcc -Wall -Wextra -Werror

$(NAME)	: $(OBJS)
	$(GCC) $(OBJS) -o $(NAME)

all	: $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all