/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:26:15 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 20:51:10 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_dat *dat)
{
	t_phi			*now;
	unsigned long	i;

	i = 0;
	now = dat->tail;
	if (pthread_create(&dat->man_th, NULL, &manager, (void *)dat))
		return (1);
	pthread_mutex_lock(&dat->start_m);
	while (i < dat->nbr)
	{
		now = now->next;
		if (pthread_create(&now->phi_th, NULL, &philosophe, (void *)now))
			return (1);
		i++;
	}
	usleep(50000);
	ft_write_val(&dat->dat_m, &dat->tm_zero, gettime(0));
	pthread_mutex_unlock(&dat->start_m);
	if (pthread_create(&dat->big_th, NULL, &bigbrother, (void *)dat))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_dat	dat;

	if (ft_check_arg(ac, av, &dat))
		return (ft_free_all(NULL, "Error: invalid parameters\n"));
	if (ft_init_phi(&dat))
		return (ft_free_all(&dat, "Error: liste chainee error\n"));
	if (start_threads(&dat))
		return (ft_end_thread(&dat, "Error: invalid thread\n"));
	ft_end_thread(&dat, NULL);
	return (0);
}
