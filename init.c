/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:25:50 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 14:45:30 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_add_elem(t_dat *dat, int i)
{
	t_phi	*phi;

	phi = malloc(sizeof(*phi));
	if (phi == NULL)
		return (1);
	phi->n = i;
	phi->dat = dat;
	if (i == 1)
	{
		dat->head = phi;
		dat->tail = phi;
		phi->next = phi;
	}
	else
	{
		phi->next = dat->head;
		dat->tail->next = phi;
		dat->tail = phi;
	}
	return (0);
}

int	ft_init_phi(t_dat *dat)
{
	int	i;

	i = 1;
	dat->head = NULL;
	dat->tail = NULL;
	while (i <= dat->nbr)
	{
		if (ft_add_elem(dat, i))
			return (1);
		pthread_mutex_init(&dat->tail->phi_m, NULL);
		pthread_mutex_init(&dat->tail->fork_m, NULL);
		dat->tail->count_eat = 0;
		dat->tail->full_eat = 0;
		dat->tail->last_eat = 0;
		i++;
	}
	return (0);
}
