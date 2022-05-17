/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:35:56 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/17 19:08:57 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void	*p)
{
	t_philo *ptr;

	ptr = (t_philo *)p;
	while(1)
	{
		pthread_mutex_lock(&ptr->data->forks[ptr->right_fork]);
		pthread_mutex_lock(&ptr->print);
		printf("\nPhilosopher %d has taking right fork", ptr->id);
		pthread_mutex_unlock(&ptr->print);
		pthread_mutex_lock(&ptr->data->forks[ptr->left_fork]);
		pthread_mutex_lock(&ptr->print);
		printf("\nPhilosopher %d has taking left fork", ptr->id);
		pthread_mutex_unlock(&ptr->print);
		pthread_mutex_lock(&ptr->print);
		printf("\nPhilosopher %d is eating", ptr->id);
		pthread_mutex_unlock(&ptr->print);
		usleep(100 * 1000);
		pthread_mutex_unlock(&ptr->data->forks[ptr->right_fork]);
		pthread_mutex_unlock(&ptr->data->forks[ptr->left_fork]);
		pthread_mutex_lock(&ptr->print);
		printf("\nPhilosopher %d is sleeping", ptr->id);
		pthread_mutex_unlock(&ptr->print);
		usleep(100 * 1000);
		pthread_mutex_lock(&ptr->print);
		printf("\nPhilosopher %d is thinking", ptr->id);
		pthread_mutex_unlock(&ptr->print);
	}
	return (NULL);
}

void	getdata(t_thread *ptr, char **argv, int argc)
{
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
	printf("%d",t.time.tv_usec);
	return 0;
	createlist(&t, &p, argc, argv);
	i = 0;
	while(i < t.nb_ofphilos)
	{
		pthread_mutex_init(&t.forks[i], NULL);
		i++;
	}
	i = 0;
	temp = p;
	while(i < t.nb_ofphilos)
	{
		pthread_mutex_init(&temp->print, NULL);
		pthread_create(&temp->philo, NULL, &routine, temp);
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


















// void *routine(void	*p)
// {
// 	t_thread *ptr;

// 	ptr = (t_thread *)p;
// 	pthread_mutex_lock(&ptr->mutex);
// 	for( int i = 0; i < 500; i++)
// 		ptr->nb++;
// 	pthread_mutex_unlock(&ptr->mutex);

// 	return NULL;
// }

	// pthread_t t1, t2;
	// t_thread	t;

	// t.nb = 0;
	// pthread_mutex_init(&t.mutex, NULL);
	// pthread_create(&t1, NULL, &routine, &t);
	// pthread_create(&t2, NULL, &routine, &t);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	// pthread_mutex_destroy(&t.mutex);
	// printf("nb  == %d\n", t.nb);