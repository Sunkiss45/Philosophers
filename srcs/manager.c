/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:07:19 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 16:07:40 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rotate_eat(t_dat *dat)
{
	pthread_mutex_lock(&dat->dat_m);
	if ((dat->nbr % 2 == 0 && dat->half_full == dat->nbr / 2)
		|| (dat->nbr % 2 == 1 && dat->half_full == dat->nbr / 2 + 1
			&& dat->sig == ODD)
		|| (dat->nbr % 2 == 1  && dat->half_full == dat->nbr / 2
			&& dat->sig == EVEN))
	{
		if (dat->sig == EVEN)
			dat->sig = ODD;
		else if (dat->sig == ODD)
			dat->sig = EVEN;
		dat->half_full = 0;
	}
	pthread_mutex_unlock(&dat->dat_m);
}

void	*manager(void *arg)
{
	t_dat	*dat;

	dat = (t_dat *)arg;
	while (ft_read_val(&dat->dat_m, &dat->sig) != SIG_END)
	{
		if (ft_read_val(&dat->dat_m, &dat->half_full)
			>= ft_read_val(&dat->dat_m, &dat->nbr) / 2)
			rotate_eat(dat);
		usleep(1000);
	}
	return (NULL);
}
