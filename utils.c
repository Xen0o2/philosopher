/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:59:17 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/11 15:58:24 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_atoi(const char *s)
{
	long long int	result;
	int				sign;

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

unsigned long	ms(void)
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