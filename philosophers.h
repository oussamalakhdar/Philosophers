/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:36:07 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/17 19:07:29 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct p_philo
{
	int	id;
	int	right_fork;
	int	left_fork;
	unsigned int	last_meal;
	pthread_mutex_t	print;
	pthread_t	philo;
	struct p_thread *data;
	struct p_philo *next;
}	t_philo;

typedef struct p_thread
{
	int	nb_ofphilos;
	int	time_todie;
	int	time_toeat;
	int	time_tosleep;
	int	times_musteat;
	struct timeval time;
	pthread_mutex_t	*forks;
} t_thread;

int		ft_atoi(const char *str);
t_philo	*ft_lstnew(t_thread *t, int id);
void	ft_lstadd_back(t_philo **lst, t_philo *new);

#endif