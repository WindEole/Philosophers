/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:50:51 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/01 19:55:40 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_read_int(pthread_mutex_t *mut, int *val)
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
		printf(YELLOW"[%llu ms] "RED"phi[%d] "RESET"%s\n",
			gettime(ft_read_llu(&phi->phi_m, &phi->tm_zero)),
			ft_read_int(&phi->phi_m, &phi->n), s);
	}
	pthread_mutex_unlock(&dat->print_m);
}
