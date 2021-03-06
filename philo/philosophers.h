/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:36:07 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/31 22:08:02 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct p_thread
{
	int				nb_ofphilos;
	int				time_todie;
	int				time_toeat;
	int				time_tosleep;
	int				times_musteat;
	pthread_mutex_t	print;
	struct timeval	time;
	pthread_mutex_t	*forks;
}	t_thread;

typedef struct p_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	long long		last_meal;
	int				meals_count;
	int				eating;
	pthread_t		philo;
	struct p_thread	*data;
	struct p_philo	*next;
}	t_philo;

int				ft_atoi(const char *str);
t_philo			*ft_lstnew(t_thread *t, int id, int i);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
long long		getnow(struct timeval t1);
int				createlist(t_thread	*t, t_philo **p, int argc, char **argv);
int				check_char(char **argv);
int				check_negative(t_thread *p);
void			getdata(t_thread *ptr, char **argv, int argc);
void			mutex_init(t_thread *ptr);
void			mutex_destroy(t_thread *ptr);
int				check_meals(t_philo *p);
void			checkdeath(t_philo	*p);
void			isleep(long time, t_philo *ptr);

#endif