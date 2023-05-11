/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:08:57 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/11 18:03:40 by alecoutr         ###   ########.fr       */
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

# define WRONG_USAGE "\x1b[31mUtilisation : ./philo <number_of_philosophers>\
 <time_to_die> <time_to_eat> <time_to_sleep>\
 (number_of_times_each_philosopher_must_eat)\x1b[0m\n"

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

long long int	ft_atoi(const char *s, int i);
int				ft_usleep(long int time_in_ms, t_philo *current);
long			ms(void);
int				is_dead(t_philo *current);
int				check_input(int ac, char **av, t_info *info);
t_philo			*init_philo(t_info *info, t_philo *first, t_philo *current);
int				routine_continue(t_philo *current);
void			*routine(void *args);
void			bigfree(t_philo *head);

#endif