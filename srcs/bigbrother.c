/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigbrother.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:28:14 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 18:35:50 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_going_to_die(t_phi *phi, t_dat *dat)
{
	if (gettime(ft_read_val(&dat->dat_m, &dat->tm_zero))
		- ft_read_val(&phi->phi_m, &phi->last_eat)
		> ft_read_val(&dat->dat_m, &dat->tm_die))
	{
		ft_print(phi, "died");
		ft_write_val(&dat->dat_m, &dat->sig, SIG_END);
	}
}

unsigned long	is_going_to_eat(t_phi *now, t_dat *dat, unsigned long i)
{
	if (ft_read_val(&now->phi_m, &now->full_eat) != EAT_OK
		&& ft_read_val(&now->phi_m, &now->count_eat)
		== ft_read_val(&dat->dat_m, &dat->round))
	{
		i++;
		ft_write_val(&now->phi_m, &now->full_eat, EAT_OK);
	}
	if (i == ft_read_val(&dat->dat_m, &dat->nbr))
	{
		ft_write_val(&dat->dat_m, &dat->sig, SIG_END);
		ft_write_val(&dat->dat_m, &dat->print, PRINT_KO);
	}
	return (i);
}

void	*bigbrother(void *arg)
{
	t_dat			*dat;
	t_phi			*now;
	unsigned long	i;

	dat = (t_dat *)arg;
	now = dat->tail;
	i = 0;
	while (ft_read_val(&dat->dat_m, &dat->sig) != SIG_END)
	{
		now = now->next;
		if (ft_read_val(&dat->dat_m, &dat->round) != (ULONG_MAX - 1))
			i = is_going_to_eat(now, dat, i);
		is_going_to_die(now, dat);
	}
	return (NULL);
}
