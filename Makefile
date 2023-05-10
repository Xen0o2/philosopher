# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 10:17:25 by alecoutr          #+#    #+#              #
#    Updated: 2023/05/10 15:31:02 by alecoutr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	=   philo.c \
			utils.c
			
OBJS	= $(SRCS:.c=.o)

GCC		= gcc -Wall -Wextra -Werror -g -g3

$(NAME)	: $(OBJS)
	$(GCC) $(OBJS) -o $(NAME)

all	: $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all