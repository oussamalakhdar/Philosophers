/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olakhdar <olakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:26:02 by olakhdar          #+#    #+#             */
/*   Updated: 2022/05/31 20:50:18 by olakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_negativextra(t_thread *ptr)
{
	if (ptr->times_musteat == 0)
	{
		printf("Number of meals is invalid!\n");
		return (0);
	}
	else
		return (1);
}

int	check_negative(t_thread *p)
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
	if (!(check_negativextra(p)))
		return (0);
	return (1);
}

int	check_char(char **argv)
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
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57) && !(argv[i][j] == 43))
			{
				printf("The arguments should be a Numbers!\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
