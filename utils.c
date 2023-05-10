/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:59:17 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/10 18:37:49 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int	result;
	int	sign;

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

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ms();
	while ((ms() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}