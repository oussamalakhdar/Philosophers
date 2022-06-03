/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:35:56 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/31 22:01:06 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(t_philo *ptr, char *str)
{
	pthread_mutex_lock(&ptr->data->print);
	printf("%llu\t%d\t%s\n", getnow(ptr->data->time), ptr->id, str);
	pthread_mutex_unlock(&ptr->data->print);
}

void	*routine(void	*p)
{
	t_philo	*ptr;

	ptr = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&ptr->data->forks[ptr->right_fork]);
		printing(ptr, "has taken a fork");
		pthread_mutex_lock(&ptr->data->forks[ptr->left_fork]);
		ptr->last_meal = getnow(ptr->data->time);
		printing(ptr, "has taken a fork");
		printing(ptr, "is eating");
		ptr->meals_count++;
		ptr->eating = 1;
		isleep(ptr->data->time_toeat, ptr);
		ptr->eating = 0;
		printing(ptr, "is sleeping");
		pthread_mutex_unlock(&ptr->data->forks[ptr->right_fork]);
		pthread_mutex_unlock(&ptr->data->forks[ptr->left_fork]);
		isleep(ptr->data->time_tosleep, ptr);
		printing(ptr, "is thinking");
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_thread	t;
	t_philo		*p;
	t_philo		*temp;
	int			i;

	i = 0;
	p = NULL;
	gettimeofday(&t.time, NULL);
	if (argc == 5 || argc == 6)
	{
		if (!(createlist(&t, &p, argc, argv)))
			return (0);
		mutex_init(&t);
		temp = p;
		while (i < t.nb_ofphilos)
		{
			pthread_create(&temp->philo, NULL, &routine, temp);
			usleep(50);
			i++;
			temp = temp->next;
		}
		checkdeath(p);
		mutex_destroy(&t);
	}
	return (0);
}
