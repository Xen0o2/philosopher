/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:08:57 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/10 18:37:57 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[33m"
# define RESET "\x1b[0m"

# define WRONG_USAGE "Utilisation : ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> (number_of_times_each_philosopher_must_eat)"

typedef struct s_info
{
	int		ac;
	char	**av;
	int		index;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
    int				philo_id;
    int				number_eat;
    int				is_dead;
	int				size;

    unsigned long	time_to_die;
    unsigned long	time_to_eat;
    unsigned long	time_to_sleep;
	unsigned long	last_eat;
    struct s_philo	*next;
}	t_philo;

int			    ft_atoi(const char *s);
void		    ft_usleep(long int time_in_ms);
unsigned long   ms(void);

#endif