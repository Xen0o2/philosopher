/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:59:17 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/11 18:01:38 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_atoi(const char *s, int i)
{
	long long int	result;
	int				sign;

	if (i)
	{
		result = 0;
		sign = 1;
		while ((*s == ' ' || *s == '\r' || *s == '\t')
			|| (*s == '\n' || *s == '\v' || *s == '\f'))
			s++;
		if (*s == '-' || *s == '+')
			if (*s++ == '-')
				sign = -1;
		while (*s >= '0' && *s <= '9')
			result = result * 10 + (*s++ - '0');
		return (result * sign);
	}
	while (*s)
	{
		if (*s == '.')
			return (0);
		s++;
	}
	return (1);
}

long	ms(void)
{
	static unsigned long	start = 0;
	struct timeval			a;

	gettimeofday(&a, NULL);
	if (!start)
		start = a.tv_sec * 1000 + a.tv_usec / 1000;
	return ((a.tv_sec * 1000 + a.tv_usec / 1000) - start);
}

int	ft_usleep(long int time_in_ms, t_philo *current)
{
	long int	start_time;

	start_time = ms();
	while ((ms() - start_time) < time_in_ms)
	{
		if (is_dead(current))
			return (0);
		usleep(10);
	}
	return (1);
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

int	check_input(int ac, char **av, t_info *info)
{
	int	i;
	int	value;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < 5)
	{
		value = ft_atoi(av[i], 1);
		if (value <= 0 || value > INT_MAX || !ft_atoi(av[i], 0))
			return (0);
		i++;
	}
	if (ac == 6 && (ft_atoi(av[5], 1) <= 0 || !ft_atoi(av[5], 0)))
		return (0);
	info->ac = ac;
	info->av = av;
	info->index = 1;
	return (1);
}
