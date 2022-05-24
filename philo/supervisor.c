/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:38:03 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/24 21:46:10 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void isleep(unsigned long time, t_philo *ptr)
{
	unsigned long i;
	unsigned long j;

	i = getnow(ptr->data->time);
	j = (time * 1000) - 20000;
	usleep(j);
	while(getnow(ptr->data->time) - i < time);
	
}

unsigned long getnow(struct timeval t1)
{
	struct timeval	t2;
	unsigned long long	start;
	unsigned long long	now;
	gettimeofday(&t2, NULL);
	start = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	now = t2.tv_sec * 1000 + t2.tv_usec / 1000;
	return (now - start);
}

int check_meals(t_philo *p)
{
	t_philo *ptr;

	ptr = p;
	if (p->data->times_musteat == -1)
		return (0);
	while (ptr)
	{
		if (ptr->meals_count < ptr->data->times_musteat)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void		checkdeath(t_philo	*p)
{
	t_philo *ptr;

	while(1)
	{
		if (check_meals(p))
		{
			pthread_mutex_lock(&p->data->print);
			return;
		}
		ptr = p;
		while(ptr)
		{
			if (ptr->last_meal + ptr->data->time_todie < getnow(ptr->data->time))
			{
				pthread_mutex_lock(&p->data->print);
				printf("%ld\t%d\tis dead\n", getnow(ptr->data->time), ptr->id);
				return;
			}
			ptr = ptr->next;
		}
	}
}