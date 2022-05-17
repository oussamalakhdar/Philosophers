/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:24:12 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/17 11:55:43 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo   *ft_lstnew(t_thread *t, int id)
{
   t_philo *p;
	p = malloc(sizeof(t_philo));
	if (p == NULL)
		return (NULL);
    p->id = id;
    p->right_fork = id;
    p->left_fork= (id + 1)%(t->nb_ofphilos + 1);
    p->last_meal = 0;
	p->philo = 0;
    p->data = t;
	p->next = NULL;
    return(p);
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
