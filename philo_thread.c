/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:27:48 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 14:56:30 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fork(t_phi *phi, t_dat *dat)
{
	pthread_mutex_lock(&phi->fork_m);
	ft_print(phi, "has taken a fork");
	if (ft_read_val(&dat->data_m, &dat->nbr) == 1)
	{
		while (ft_read_val(&dat->data_m, &dat->sig) != SIG_END)
			usleep(500);
		pthread_mutex_unlock(&phi->fork_m);
		return (1);
	}
	pthread_mutex_lock(&phi->next->fork_m);
	ft_print(phi, "has taken a fork");
	return (0);
}

void	ft_eat(t_phi *phi, t_dat *dat)
{
	ft_print(phi, "is eating");
	ft_write_val(&phi->phi_m, &phi->last_eat,
		gettime(ft_read_val(&phi->phi_m, &phi->tm_zero)));
	ft_write_val(&phi->phi_m, &phi->eat_n, phi->eat_n + 1);
	ft_write_val(&dat->eat_m, &dat->sig_eat,
		ft_read_val(&dat->eat_m, &dat->sig_eat) + 1);
	prec_wait(ft_read_val(&dat->data_m, &dat->tm_eat), phi);
	pthread_mutex_unlock(&phi->next->fork_m);
	pthread_mutex_unlock(&phi->fork_m);
}

void	*philosophe(void *arg)
{
	t_phi	*phi;
	t_dat	*dat;

	phi = (t_phi *)arg;
	dat = phi->dat;
	while (ft_read_val(&dat->data_m, &dat->sig) != SIG_END)
	{
		if ((ft_read_val(&dat->data_m, &dat->sig) == ODD
				&& ft_read_val(&phi->phi_m, &phi->n) % 2 == 1)
			|| (ft_read_val(&dat->data_m, &dat->sig) == EVEN
				&& ft_read_val(&phi->phi_m, &phi->n) % 2 == 0))
		{
			if (ft_fork(phi, dat))
				return (NULL);
			ft_eat(phi, dat);
			ft_print(phi, "is sleeping");
			prec_wait(ft_read_val(&dat->data_m, &dat->tm_sle), phi);
			ft_print(phi, "is thinking");
		}
	}
	return (NULL);
}
