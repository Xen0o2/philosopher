/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:09:03 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/11 18:02:48 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_info *info, t_philo *first, t_philo *current)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->philo_id = info->index++;
	new_philo->is_dead = 0;
	new_philo->size = ft_atoi(info->av[1], 1);
	new_philo->time_to_die = ft_atoi(info->av[2], 1);
	new_philo->time_to_eat = ft_atoi(info->av[3], 1);
	new_philo->time_to_sleep = ft_atoi(info->av[4], 1);
	new_philo->last_eat = 0;
	pthread_mutex_init(&new_philo->fork, NULL);
	if (info->ac == 6)
		new_philo->number_eat = ft_atoi(info->av[5], 1);
	else
		new_philo->number_eat = -1;
	if (current)
		current->next = new_philo;
	else
		first = new_philo;
	if (info->index - 1 == new_philo->size)
	{
		new_philo->next = first;
		return (first);
	}
	return (init_philo(info, first, new_philo));
}

int	routine_continue(t_philo *current)
{
	pthread_mutex_unlock(&current->fork);
	pthread_mutex_unlock(&current->next->fork);
	if (current->number_eat == 0)
		return (0);
	if (is_dead(current))
		return (0);
	printf("%lu %d is sleeping\n", ms(), current->philo_id);
	if (!ft_usleep(current->time_to_sleep, current))
		return (0);
	if (is_dead(current))
		return (0);
	printf("%lu %d is thinking\n", ms(), current->philo_id);
	return (1);
}

void	*routine(void *args)
{
	t_philo	*current;

	current = (t_philo *)args;
	if (current->philo_id % 2 == 0)
		ft_usleep(current->time_to_eat, current);
	while (1)
	{
		pthread_mutex_lock(&current->fork);
		printf("%lu %d has taken a fork\n", ms(), current->philo_id);
		if (is_dead(current))
			return (NULL);
		pthread_mutex_lock(&current->next->fork);
		printf("%lu %d has taken a fork\n", ms(), current->philo_id);
		current->last_eat = ms();
		printf("%lu %d is eating\n", ms(), current->philo_id);
		ft_usleep(current->time_to_eat, current);
		current->number_eat--;
		if (!routine_continue(current))
			return (NULL);
		if (is_dead(current))
			return (NULL);
	}
	return (NULL);
}

void	bigfree(t_philo *head)
{
	int		i;
	int		nb_philo;
	t_philo	*next;

	i = 0;
	nb_philo = head->size;
	while (i++ < nb_philo)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

int	main(int ac, char **av)
{
	t_philo	*current;
	t_info	info;
	int		i;

	if (!check_input(ac, av, &info))
		return (printf(WRONG_USAGE), 0);
	current = init_philo(&info, NULL, NULL);
	i = -1;
	while (++i < current->size)
	{
		pthread_create(&current->thread, NULL, &routine, current);
		current = current->next;
	}
	i = -1;
	while (++i < current->size)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	while (--i)
	{
		pthread_detach(current->thread);
		current = current->next;
	}
	bigfree(current);
}
