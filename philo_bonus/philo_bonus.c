/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:19:37 by olakhdar          #+#    #+#             */
/*   Updated: 2022/06/01 19:31:28 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing(t_philo *ptr, char *str)
{
	sem_wait(ptr->data->print);
	printf("%ld\t%d\t%s\n", getnow(ptr->data->time), ptr->id, str);
	sem_post(ptr->data->print);
}

void	routine(t_philo	*ptr)
{
	pthread_create(&ptr->philo, NULL, &supervisor, ptr);
	while (ptr->data->times_musteat == -1
		|| (ptr->data->times_musteat != -1
			&& ptr->meals_count < ptr->data->times_musteat))
	{
		sem_wait(ptr->data->fork);
		printing(ptr, "has taken a fork");
		sem_wait(ptr->data->fork);
		ptr->last_meal = getnow(ptr->data->time);
		printing(ptr, "has taken a fork");
		printing(ptr, "is eating");
		ptr->meals_count += 1;
		ptr->eating = 1;
		isleep(ptr->data->time_toeat, ptr);
		ptr->eating = 0;
		printing(ptr, "is sleeping");
		sem_post(ptr->data->fork);
		sem_post(ptr->data->fork);
		isleep(ptr->data->time_tosleep, ptr);
		printing(ptr, "is thinking");
	}
	exit(0);
}

void	init_semaphores(t_philo *p)
{
	sem_unlink("forks");
	sem_unlink("print");
	p->data->fork = sem_open("forks", O_CREAT, 0666, p->data->nb_ofphilos);
	p->data->print = sem_open("print", O_CREAT, 0666, 1);
}

void	create_childs(t_philo *p, t_thread *t)
{
	t_philo	*temp;
	int		i;

	i = 0;
	temp = p;
	while (i < t->nb_ofphilos)
	{
		temp->pid = fork();
		if (temp->pid == -1)
		{
			printf("fork Error!\n");
			exit(1);
		}
		else if (temp->pid == 0)
			routine(temp);
		temp = temp->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_thread	t;
	t_philo		*p;
	t_philo		*temp;

	p = NULL;
	gettimeofday(&t.time, NULL);
	if (argc == 5 || argc == 6)
	{
		if (!(createlist(&t, &p, argc, argv)))
			return (0);
		init_semaphores(p);
		create_childs(p, &t);
		temp = p;
		if (t.times_musteat > 0)
		{
			while (temp)
			{
				waitpid(-1, NULL, 0);
				temp = temp->next;
			}
		}
		else
			waitpid(-1, NULL, 0);
	}
	return (0);
}
