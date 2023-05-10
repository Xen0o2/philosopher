/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:09:03 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/10 18:55:15 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char	*message)
{
	printf("%s%s%s\n", RED, message, RESET);
	return (0);
}

int	check_input(int ac, char **av, t_info *info)
{
	if (ac < 5 || ac > 6)
		return (0);
	if (ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
		|| ft_atoi(av[4]) < 0)
		return (0);
	if (ac == 6 && ft_atoi(av[5]) < 0)
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

void	*routine(void *args)
{
	t_philo	*current;

	current = (t_philo *)args;
	
	
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	*current;
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
}
