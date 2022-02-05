/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:26:45 by ebarguil          #+#    #+#             */
/*   Updated: 2022/02/05 15:03:46 by ebarguil         ###   ########.fr       */
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
	unsigned long	tm_zero;
	struct s_dat	*dat;
	struct s_phi	*next;
}	t_phi;

typedef struct s_dat
{
	pthread_t		eat_th;
	pthread_t		die_th;
	pthread_mutex_t	data_m;
	pthread_mutex_t	print_m;
	unsigned long	nbr;
	unsigned long	tm_die;
	unsigned long	tm_eat;
	unsigned long	tm_sle;
	unsigned long	round;
	unsigned long	sig;
	unsigned long	print;
	unsigned long	half_full;
	struct s_phi	*head;
	struct s_phi	*tail;
}	t_dat;

/////     init.c     /////

int					ft_add_elem(t_dat *dat, int i);
int					ft_init_phi(t_dat *dat);
int					ft_check_arg(int ac, char **av, t_dat *dat);

/////     philo_thread.c     /////

void				*philosophe(void *arg);

/////     time.c     /////

void				go_die(t_phi *phi, t_dat *dat);
void				*routine_bigb(void *arg);
void				prec_wait(unsigned long delay, t_phi *phi);
unsigned long		gettime(unsigned long tm_zero);

/////    print.c     /////

/*int					ft_read_int(pthread_mutex_t *mut, int *val);
unsigned long long	ft_read_llu(pthread_mutex_t *mut, unsigned long long *val);
void				ft_write_int(pthread_mutex_t *mut, int *val, int i);
void				ft_write_llu(pthread_mutex_t *mut, unsigned long long *val,
						unsigned long long i);*/
unsigned long		ft_read_val(pthread_mutex_t *mut, unsigned long *val);
void				ft_write_val(pthread_mutex_t *mut, unsigned long *val,
						unsigned long i);
void				ft_print(t_phi *phi, char *s);

/////     end.c     /////

int					ft_free_all(t_dat *dat, char *s);
int					ft_end_thread(t_dat *dat, char *s);

#endif
