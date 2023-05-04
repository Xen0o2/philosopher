/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:09:03 by alecoutr          #+#    #+#             */
/*   Updated: 2023/05/03 18:20:28 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine1(void *args)
{
	int	i;

	i = 0;
	while (i++ < 100000);
	i = 0;
	while (i++ < 10)
		printf("T1 : %d\n", i);
	return (NULL);
}
void	*routine2(void *args)
{
	int	i;

	i = 0;
	while (i++ < 10)
		printf("T2 : %d\n", i);
	return (NULL);
}

int main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, routine1, NULL);
	pthread_create(&t2, NULL, routine2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}