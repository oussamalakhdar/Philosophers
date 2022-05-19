/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:35:56 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/19 21:32:13 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void ft_sleep(int i)
// {
// 	while(i > 0)
// 		i--;
// 	return;
// }

void	*checkdeath(void	*p)
{
	t_philo *ptr;

	ptr = (t_philo *)p;
	while(1)
	{
		if (ptr->last_meal + ptr->data->time_todie < getnow(ptr->data->time))
		{
			printf("%ld\t%d\tis dead\n", getnow(ptr->data->time), ptr->id);
			exit(1);
		}
	}
	return (NULL);
}

long	getnow(struct timeval t1)
{
	struct timeval	t2;
	unsigned long long	start;
	unsigned long long	now;
	gettimeofday(&t2, NULL);
	start = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	now = t2.tv_sec * 1000 + t2.tv_usec / 1000;
	return (now - start);
}

void print_takenfork(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->print);
	printf("%ld\t%d\thas taken a fork\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->print);
}

void print_eating(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->print);
	printf("%ld\t%d\tis eating\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->print);
}

void print_sleeping(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->print);
	printf("%ld\t%d\tis sleeping\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->print);
}

void print_thinking(t_philo *ptr)
{
	pthread_mutex_lock(&ptr->print);
	printf("%ld\t%d\tis thinking\n", getnow(ptr->data->time), ptr->id);
	pthread_mutex_unlock(&ptr->print);
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
		usleep(ptr->data->time_toeat * 1000);
		pthread_mutex_unlock(&ptr->data->forks[ptr->right_fork]);
		pthread_mutex_unlock(&ptr->data->forks[ptr->left_fork]);
		print_sleeping(ptr);
		usleep(ptr->data->time_tosleep * 1000);
		print_thinking(ptr);
	}
	return (NULL);
}

void	getdata(t_thread *ptr, char **argv, int argc)
{
	// while(str[i])
	// {
	// 	if (!(str[i] >=48 && str[i] <= 57))
	// 	{	
	// 		printf("Error");
	// 		return 0;
	// 	}
	// }
	ptr->nb_ofphilos = ft_atoi(argv[1]);
	ptr->time_todie = ft_atoi(argv[2]);
	ptr->time_toeat = ft_atoi(argv[3]);
	ptr->time_tosleep = ft_atoi(argv[4]);
	if (argc == 6)
		ptr->times_musteat = ft_atoi(argv[5]);
	ptr->forks = malloc(sizeof(pthread_mutex_t) * ptr->nb_ofphilos);
}

void	createlist(t_thread	*t, t_philo **p, int argc, char **argv)
{
	t_philo		*new;
	int id;
	int i;

	i = 0;
	id = 1;
	new = NULL;
	getdata(t, argv, argc);
	while(i < t->nb_ofphilos)
	{
		new = ft_lstnew(t, id);
		ft_lstadd_back(p, new);
		i++;
		id++;
	}
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
	createlist(&t, &p, argc, argv);
	i = 0;
	while(i < t.nb_ofphilos)
	{
		pthread_mutex_init(&t.forks[i], NULL);
		i++;
	}
	pthread_create(&p->data->death, NULL, &checkdeath, p);
	i = 0;
	temp = p;
	while(i < t.nb_ofphilos)
	{
		pthread_mutex_init(&temp->print, NULL);
		pthread_create(&temp->philo, NULL, &routine, temp);
		// pthread_create(&temp->death, NULL, &checkdeath, temp);
		usleep(1000);
		i++;
		temp = temp->next;
	}
	i = 0;
	temp = p;
	while(i < t.nb_ofphilos)
	{
		pthread_join(temp->philo, NULL);
		temp = temp->next;
		i++;
	}
	i = 0;
	while(i < t.nb_ofphilos)
	{
		pthread_mutex_destroy(&t.forks[i]);
	}
	return 0;
}
