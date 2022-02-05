/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:26:15 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 14:52:28 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rotate_eat(t_dat *dat)
{
	pthread_mutex_lock(&dat->data_m);
	if (dat->nbr % 2 == 0 && dat->half_full == dat->nbr / 2
		|| dat->nbr % 2 == 1 && dat->half_full == dat->nbr / 2 + 1
			&& dat->sig == ODD
		|| dat->nbr % 2 == 1  && dat->half_full == dat->nbr / 2
			&& dat->sig == EVEN)
	{
		if (dat->sig == EVEN)
			dat->sig = ODD;
		else if (dat->sig == ODD)
			dat->sig = EVEN;
		dat->half_full = 0;
	}
	pthread_mutex_unlock(&dat->data_m);
}

void	*manager(void *arg)
{
	t_dat	*dat;

	dat = (t_dat *)arg;
	while (ft_read_val(&dat->data_m, &dat->sig) != SIG_END)
	{
		if (ft_read_val(&dat->data_m, &dat->half_full)
			>= ft_read_val(&dat->data_m, &dat->nbr) / 2)
			rotate_eat(dat);
		usleep(1000);
	}
	return (NULL);
}

int	start_threads(t_dat *dat)
{
	t_phi	*now;
	int		i;

	i = 0;
	now = dat->tail;
	if (pthread_create(&dat->eat_th, NULL, &manager, (void *)dat))
		return (1);
	while (i < dat->nbr)
	{
		now = now->next;
		now->tm_zero = gettime(0);
		if (pthread_create(&now->phi_th, NULL, &philosophe, (void *)now))
			return (1);
		i++;
	}
	if (pthread_create(&dat->die_th, NULL, &routine_bigb, (void *)dat))
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
	while (ft_read_val(&dat.data_m, &dat.sig) != SIG_END)
		usleep(500);
	ft_end_thread(&dat, NULL);
	return (0);
}
