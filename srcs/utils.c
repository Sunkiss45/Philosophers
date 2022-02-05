/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:18:57 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 18:38:56 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gettime(unsigned long time_zero)
{
	struct timeval		current;
	unsigned long	time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	if (time_zero > 0)
		time -= time_zero;
	return (time);
}

unsigned long	ft_read_val(pthread_mutex_t *mut, unsigned long *val)
{
	unsigned long	r;

	pthread_mutex_lock(mut);
	r = *val;
	pthread_mutex_unlock(mut);
	return (r);
}

void	ft_write_val(pthread_mutex_t *mut, unsigned long *val, unsigned long i)
{
	pthread_mutex_lock(mut);
	*val = i;
	pthread_mutex_unlock(mut);
}

void	prec_wait(unsigned long delay, t_dat *dat)
{
	unsigned long	final;

	final = gettime(ft_read_val(&dat->dat_m, &dat->tm_zero)) + delay;
	while (ft_read_val(&dat->dat_m, &dat->sig) != SIG_END
		&& gettime(ft_read_val(&dat->dat_m, &dat->tm_zero)) < final)
		usleep(1000);
	return ;
}

void	ft_print(t_phi *phi, char *s)
{
	t_dat	*dat;

	dat = phi->dat;
	if (ft_read_val(&dat->print_m, &dat->print) == PRINT_KO)
		return ;
	pthread_mutex_lock(&dat->print_m);
	if (ft_read_val(&dat->dat_m, &dat->print) == PRINT_OK
		&& ft_read_val(&dat->dat_m, &dat->sig) != SIG_END)
	{
		if (s[0] == 'd')
			ft_write_val(&dat->dat_m, &dat->print, PRINT_KO);
		printf("%lu %lu %s\n",
			gettime(ft_read_val(&dat->dat_m, &dat->tm_zero)),
			ft_read_val(&phi->phi_m, &phi->n), s);
	}
	pthread_mutex_unlock(&dat->print_m);
}

/*
printf(YELLOW"[%lu ms] "RED"phi[%lu] "RESET"%s\n"
*/
