/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:36:07 by olakhdar          #+#    #+#             */
/*   Updated: 2022/06/01 19:21:14 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct p_thread
{
	int				nb_ofphilos;
	int				time_todie;
	int				time_toeat;
	int				time_tosleep;
	int				times_musteat;
	sem_t			*print;
	sem_t			*fork;
	struct timeval	time;
}	t_thread;

typedef struct p_philo
{
	int				id;
	pid_t			pid;
	unsigned long	last_meal;
	int				meals_count;
	int				eating;
	pthread_t		philo;
	struct p_thread	*data;
	struct p_philo	*next;
}	t_philo;

int				ft_atoi(const char *str);
t_philo			*ft_lstnew(t_thread *t, int id);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
int				createlist(t_thread	*t, t_philo **p, int argc, char **argv);
void			*supervisor(void	*p);
void			isleep(unsigned long time, t_philo *ptr);
unsigned long	getnow(struct timeval t1);
int				check_negativextra(t_thread *ptr);
int				check_negative(t_thread *p);
int				check_char(char **argv);
int				check_meals(t_philo *p);

#endif