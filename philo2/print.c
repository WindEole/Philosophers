/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:50:51 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/05 20:13:34 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	read_val(pthread_mutex_t *mut, unsigned long *val)
{
	unsigned long	r;

	pthread_mutex_lock(mut);
	r = *val;
	pthread_mutex_unlock(mut);
	return (r);
}

void	write_val(pthread_mutex_t *mut, unsigned long *val, unsigned long i)
{
	pthread_mutex_lock(mut);
	*val = i;
	pthread_mutex_unlock(mut);
}

void	ft_print(t_phi *phi, char *s)
{
	t_dat	*dat;

	dat = phi->dat;
	if (read_val(&dat->print_m, &dat->print) == PRINT_KO)
		return ;
	pthread_mutex_lock(&dat->print_m);
	if (read_val(&dat->data_m, &dat->print) == PRINT_OK
		&& read_val(&dat->data_m, &dat->sig) != SIG_END)
	{
		if (s[0] == 'd')
			write_val(&dat->data_m, &dat->print, PRINT_KO);
		printf("%lu %lu %s\n",
			gettime(read_val(&dat->data_m, &dat->tm_zero)),
			read_val(&phi->phi_m, &phi->n), s);
	}
	pthread_mutex_unlock(&dat->print_m);
}

/*
printf(YELLOW"[%lu ms] "RED"phi[%lu] "RESET"%s\n"
*/
