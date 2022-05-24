/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:35:56 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/24 21:46:07 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_takenfork(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->data->print);
	printf("%ld\t%d\thas taken a fork\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->data->print);
}

void print_eating(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->data->print);
	printf("%ld\t%d\tis eating\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->data->print);
}

void print_sleeping(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->data->print);
	printf("%ld\t%d\tis sleeping\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->data->print);
}

void print_thinking(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->data->print);
	printf("%ld\t%d\tis thinking\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->data->print);
}

void	*routine(void	*p)
{
	t_philo *ptr;

	ptr = (t_philo *)p;
	while(1)
	{
		pthread_mutex_lock(&ptr->data->forks[ptr->right_fork]);
		print_takenfork(ptr);
		pthread_mutex_lock(&ptr->data->forks[ptr->left_fork]);
		ptr->last_meal = getnow(ptr->data->time);
		print_takenfork(ptr);
		print_eating(ptr);
		ptr->meals_count++;
		isleep(ptr->data->time_toeat, ptr);
		// usleep(ptr->data->time_toeat * 1000);
		print_sleeping(ptr);
		pthread_mutex_unlock(&ptr->data->forks[ptr->right_fork]);
		pthread_mutex_unlock(&ptr->data->forks[ptr->left_fork]);
		isleep(ptr->data->time_tosleep, ptr);
		// usleep(ptr->data->time_tosleep * 1000);
		print_thinking(ptr);
	}
	return (NULL);
}

int check_negative(t_thread *p)
{
	if (p->nb_ofphilos <= 0)
	{
		printf("Wrong number of philosophers!\n");
		return (0);	
	}
	if (p->time_todie < 0)
	{
		printf("Time to die is negative!\n");
		return (0);	
	}
	if (p->time_toeat < 0)
	{
		printf("Time to eat is negative!\n");
		return (0);
	}
	if (p->time_tosleep < 0)
	{
		printf("Time to sleep is negative!\n");
		return (0);	
	}
	if (p->times_musteat == 0)
	{
		printf("Number of meals is invalid!\n");
		return (0);	
	}
	return (1);
}

int check_char(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >=48 && argv[i][j] <= 57) && !(argv[i][j] == 43))
			{
				printf("Error\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_thread	t;
	t_philo		*p;
	t_philo		*temp;
	int			i;
	
	i = 0;
	p = NULL;
	gettimeofday(&t.time, NULL); 
	if ( argc == 5 || argc == 6)
	{
		if (!(createlist(&t, &p, argc, argv)))
			return (0);
		mutex_init(&t);
		// i = 0;
		// while (i < t.nb_ofphilos)
		// {
		// 	pthread_mutex_init(&t.forks[i], NULL);
		// 	i++;
		// }
		// pthread_mutex_init(&p->data->print, NULL);
		// i = 0;
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
		// i = 0;
		// pthread_mutex_destroy(&p->data->print);
		// while (i < t.nb_ofphilos)
		// {
		// 	pthread_mutex_destroy(&t.forks[i]);
		// 	i++;
		// }
	}
	return (0);
}
