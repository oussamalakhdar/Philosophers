/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:57:31 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/30 14:23:30 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_init(t_thread *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->nb_ofphilos)
	{
		pthread_mutex_init(&ptr->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&ptr->print, NULL);
}

void	mutex_destroy(t_thread *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->nb_ofphilos)
	{
		pthread_mutex_destroy(&ptr->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&ptr->print);
}
