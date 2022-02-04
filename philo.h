/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:39:31 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/04 12:54:01 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> // memset
# include <unistd.h> // usleep
# include <sys/time.h> // gettimeofday
# include <stdlib.h> // malloc / free
# include <limits.h> // INT_MIN / INT_MAX
# include <stdio.h> // printf
# include <pthread.h> // thread functions !

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
	int					n;
	pthread_t			phi_th;
	int					eat_n;
	int					eat_ok;
	pthread_mutex_t		phi_m;
	pthread_mutex_t		fork_m;
	pthread_mutex_t		busy_m;
	pthread_mutex_t		godie_m;
	unsigned long long	last_eat;
	unsigned long long	tm_zero;
	struct s_dat		*dat;
	struct s_phi		*next;
}	t_phi;

typedef struct s_dat
{
	int				nbr;
	int				tm_die;
	pthread_t		die_th;
	int				tm_eat;
	pthread_t		eat_th;
	int				tm_sle;
	int				round;
	int				sig;
	int				sig_print;
	int				sig_eat;
	pthread_mutex_t	eat_m;
	pthread_mutex_t	print_m;
	pthread_mutex_t	data_m;
	struct s_phi	*head;
	struct s_phi	*tail;
}	t_dat;

/////     init.c     /////

int					ft_add_elem(t_dat *dat, int i);
int					ft_init_phi(t_dat *dat);
int					ft_check_arg(int ac, char **av, t_dat *dat);

/////     philo_thread.c     /////

void				*routine_phi(void *arg);

/////     time.c     /////

void				go_die(t_phi *phi, t_dat *dat);
void				*routine_bigb(void *arg);
void				prec_sleep(unsigned long long delay, t_phi *phi);
unsigned long long	gettime(unsigned long long tm_zero);

/////    print.c     /////

int					ft_read_int(pthread_mutex_t *mut, int *val);
unsigned long long	ft_read_llu(pthread_mutex_t *mut, unsigned long long *val);
void				ft_write_int(pthread_mutex_t *mut, int *val, int i);
void				ft_write_llu(pthread_mutex_t *mut, unsigned long long *val,
						unsigned long long i);
void				ft_print(t_phi *phi, char *s);

/////     end.c     /////

int					ft_free_all(t_dat *dat, char *s);
int					ft_end_thread(t_dat *dat, char *s);

#endif
