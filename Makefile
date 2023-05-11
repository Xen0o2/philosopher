# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 10:17:25 by alecoutr          #+#    #+#              #
#    Updated: 2023/05/11 17:59:20 by alecoutr         ###   ########.fr        #
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

.c.o :
	$(GCC) $(FLAGS) -c $< -o $(<:.c=.o)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all