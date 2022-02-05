/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:25:50 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 18:35:02 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atolu(char *s, t_dat *dat)
{
	int				i;
	unsigned long	res;

	i = 0;
	res = 0;
	if (s[i] == '+')
		i++;
	while (s[i] && (unsigned char)s[i] >= 48 && (unsigned char)s[i] <= 57)
	{
		res = (res * 10) + ((unsigned char)s[i] - 48);
		i++;
	}
	if (i == 0 || s[i] != '\0' || res > INT_MAX || i > 11)
		dat->sig = SIG_END;
	return (res);
}

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
	unsigned long	i;

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

int	ft_check_arg(int ac, char **av, t_dat *dat)
{
	if (ac != 5 && ac != 6)
		return (1);
	dat->print = PRINT_OK;
	dat->half_full = 0;
	dat->sig = ODD;
	dat->nbr = ft_atolu(av[1], dat);
	dat->tm_die = ft_atolu(av[2], dat);
	dat->tm_eat = ft_atolu(av[3], dat);
	dat->tm_sle = ft_atolu(av[4], dat);
	if (ac == 6)
		dat->round = ft_atolu(av[5], dat);
	else
		dat->round = -1;
	if (dat->sig == SIG_END)
		return (1);
	pthread_mutex_init(&dat->dat_m, NULL);
	pthread_mutex_init(&dat->print_m, NULL);
	pthread_mutex_init(&dat->start_m, NULL);
	return (0);
}
