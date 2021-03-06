/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:26:45 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 19:04:41 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

# define ODD 1
# define EVEN 2
# define SIG_END 7
# define EAT_OK 8
# define PRINT_OK 42
# define PRINT_KO 21

typedef struct s_phi
{
	pthread_t		phi_th;
	pthread_mutex_t	phi_m;
	pthread_mutex_t	fork_m;
	unsigned long	n;
	unsigned long	count_eat;
	unsigned long	full_eat;
	unsigned long	last_eat;
	struct s_dat	*dat;
	struct s_phi	*next;
}	t_phi;

typedef struct s_dat
{
	pthread_t		man_th;
	pthread_t		big_th;
	pthread_mutex_t	dat_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	start_m;
	unsigned long	nbr;
	unsigned long	tm_die;
	unsigned long	tm_eat;
	unsigned long	tm_sle;
	unsigned long	round;
	unsigned long	tm_zero;
	unsigned long	sig;
	unsigned long	print;
	unsigned long	half_full;
	struct s_phi	*head;
	struct s_phi	*tail;
}	t_dat;

/* /////   main.c   ///// */

int				start_threads(t_dat *dat);

/* /////   parsing.c   ///// */

unsigned long	ft_atolu(char *s, t_dat *dat);
int				ft_add_elem(t_dat *dat, int i);
int				ft_init_phi(t_dat *dat);
int				ft_check_arg(int ac, char **av, t_dat *dat);

/* /////   manager.c   ///// */

void			rotate_eat(t_dat *dat);
void			*manager(void *arg);

/* /////   philosophe.c   ///// */

int				ft_fork(t_phi *phi, t_dat *dat);
void			ft_eat(t_phi *phi, t_dat *dat);
void			*philosophe(void *arg);

/* /////   bigbrother.c   ///// */

void			is_going_to_die(t_phi *phi, t_dat *dat);
unsigned long	is_going_to_eat(t_phi *now, t_dat *dat, unsigned long i);
void			*bigbrother(void *arg);

/* /////   end.c   ///// */

int				ft_free_all(t_dat *dat, char *s);
int				ft_end_thread(t_dat *dat, char *s);

/* /////   utils.c   ///// */

unsigned long	gettime(unsigned long time_zero);
unsigned long	ft_read_val(pthread_mutex_t *mut, unsigned long *val);
void			ft_write_val(pthread_mutex_t *mut, unsigned long *val,
					unsigned long i);
void			prec_wait(unsigned long delay, t_dat *dat);
void			ft_print(t_phi *phi, char *s);

#endif
