/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:24:12 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/24 21:29:45 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	getdata(t_thread *ptr, char **argv, int argc)
{
	ptr->nb_ofphilos = ft_atoi(argv[1]);
	ptr->time_todie = ft_atoi(argv[2]);
	ptr->time_toeat = ft_atoi(argv[3]);
	ptr->time_tosleep = ft_atoi(argv[4]);
	if (argc == 6)
		ptr->times_musteat = ft_atoi(argv[5]);
	else
		ptr->times_musteat = -1;
	ptr->forks = malloc(sizeof(pthread_mutex_t) * ptr->nb_ofphilos);
}

t_philo	*ft_lstnew(t_thread *t, int id, int i)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (p == NULL)
		return (NULL);
	p->id = id;
	p->right_fork = i;
	p->left_fork = (i + 1) % (t->nb_ofphilos);
	p->last_meal = 0;
	p->meals_count = 0;
	p->philo = 0;
	p->data = t;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*temp;

	temp = *lst;
	if ((*lst) == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

int	createlist(t_thread	*t, t_philo **p, int argc, char **argv)
{
	t_philo	*new;
	int		id;
	int		i;

	i = 0;
	id = 1;
	new = NULL;
	getdata(t, argv, argc);
	if (!(check_negative(t)))
		return (0);
	if (!(check_char(argv)))
		return (0);
	while (i < t->nb_ofphilos)
	{
		new = ft_lstnew(t, id, i);
		ft_lstadd_back(p, new);
		i++;
		id++;
	}
	return (1);
}
