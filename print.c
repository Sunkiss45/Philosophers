/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:28:01 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 11:44:08 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	ft_read_int(pthread_mutex_t *mut, int *val)
{
	int	r;

	pthread_mutex_lock(mut);
	r = *val;
	pthread_mutex_unlock(mut);
	return (r);
}

unsigned long long	ft_read_llu(pthread_mutex_t *mut, unsigned long long *val)
{
	unsigned long long	r;

	pthread_mutex_lock(mut);
	r = *val;
	pthread_mutex_unlock(mut);
	return (r);
}

void	ft_write_int(pthread_mutex_t *mut, int *val, int i)
{
	pthread_mutex_lock(mut);
	*val = i;
	pthread_mutex_unlock(mut);
}

void	ft_write_llu(pthread_mutex_t *mut, unsigned long long *val,
		unsigned long long i)
{
	pthread_mutex_lock(mut);
	*val = i;
	pthread_mutex_unlock(mut);
}*/

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

void	ft_print(t_phi *phi, char *s)
{
	t_dat	*dat;

	dat = phi->dat;
	if (ft_read_int(&dat->print_m, &dat->sig_print) == PRINT_KO)
		return ;
	pthread_mutex_lock(&dat->print_m);
	if (ft_read_int(&dat->data_m, &dat->sig_print) == PRINT_OK
		&& ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
	{
		if (s[0] == 'd')
			ft_write_int(&dat->data_m, &dat->sig_print, PRINT_KO);
		printf("%llu %d %s\n",
			gettime(ft_read_llu(&phi->phi_m, &phi->tm_zero)),
			ft_read_int(&phi->phi_m, &phi->n), s);
	}
	pthread_mutex_unlock(&dat->print_m);
}

/*
printf(YELLOW"[%llu ms] "RED"phi[%d] "RESET"%s\n"
*/