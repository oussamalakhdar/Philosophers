/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:38:03 by olakhdar          #+#    #+#             */
/*   Updated: 2022/06/01 19:31:18 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	isleep(unsigned long time, t_philo *ptr)
{
	unsigned long	i;
	unsigned long	j;

	i = getnow(ptr->data->time);
	j = (time * 1000) - 20000;
	usleep(j);
	while (getnow(ptr->data->time) - i < time)
		;
}

unsigned long	getnow(struct timeval t1)
{
	struct timeval		t2;
	unsigned long long	start;
	unsigned long long	now;

	gettimeofday(&t2, NULL);
	start = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	now = t2.tv_sec * 1000 + t2.tv_usec / 1000;
	return (now - start);
}

void	*supervisor(void	*p)
{
	t_philo	*ptr;

	ptr = (t_philo *)p;
	while (1)
	{
		if (ptr->last_meal + ptr->data->time_todie
			< getnow(ptr->data->time) && ptr->eating == 0)
		{
			sem_wait(ptr->data->print);
			printf("%ld\t%d\tis dead\n", getnow(ptr->data->time), ptr->id);
			exit(0);
		}
	}
	return (NULL);
}
