/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:09:03 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/11 17:23:36 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char	*message)
{
	printf("%s%s%s\n", RED, message, RESET);
	return (0);
}

int	is_int(char *value)
{
	while (*value)
	{
		if (*value == '.')
			return (0);
		value++;
	}
	return (1);
}

int	check_input(int ac, char **av, t_info *info)
{
	int	i;
	int	value;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < 5)
	{
		value = ft_atoi(av[i]);
		if (value <= 0 || value > INT_MAX || !is_int(av[i]))
			return (0);
		i++;
	}
	if (ac == 6 && (ft_atoi(av[5]) <= 0 || !is_int(av[5])))
		return (0);
	info->ac = ac;
	info->av = av;
	info->index = 1;
	return (1);
}

t_philo	*init_philo(t_info *info, t_philo *first, t_philo *current)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->philo_id = info->index++;
	new_philo->is_dead = 0;
	new_philo->size = ft_atoi(info->av[1]);
	new_philo->time_to_die = ft_atoi(info->av[2]);
	new_philo->time_to_eat = ft_atoi(info->av[3]);
	new_philo->time_to_sleep = ft_atoi(info->av[4]);
	pthread_mutex_init(&new_philo->fork, NULL);
	if (info->ac == 6)
		new_philo->number_eat = ft_atoi(info->av[5]);
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

int	is_dead(t_philo *current)
{
	int	i;

	i = 0;
	if (current->size == 1)
	{
		current->size = 0;
		ft_usleep(current->time_to_die, current);
		printf("%lu %d has died\n", ms(), current->philo_id);
		return (1);
	}
	while (i++ < current->size)
	{
		if (current->is_dead == 1)
			return (1);
		current = current->next;
	}
	if (current->time_to_die < ms() - current->last_eat)
	{
		current->is_dead = 1;
		printf("%lu %d has died\n", ms(), current->philo_id);
		return (1);
	}
	return (0);
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
		pthread_mutex_unlock(&current->fork);
		pthread_mutex_unlock(&current->next->fork);
		if (current->number_eat == 0)
			return (NULL);
		if (is_dead(current))
			return (NULL);
		printf("%lu %d is sleeping\n", ms(), current->philo_id);
		if (!ft_usleep(current->time_to_sleep, current))
			return (NULL);
		if (is_dead(current))
			return (NULL);
		printf("%lu %d is thinking\n", ms(), current->philo_id);
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
	t_philo	*tmp;
	t_info	info;
	int		i;

	if (!check_input(ac, av, &info))
		return (ft_error(WRONG_USAGE));
	current = init_philo(&info, NULL, current);
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
	i = -1;
	while (++i < current->size)
	{
		pthread_detach(current->thread);
		current = current->next;
	}
	bigfree(current);
}
