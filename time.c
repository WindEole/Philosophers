/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:09:01 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/04 13:07:41 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_die(t_phi *phi, t_dat *dat)
{
	pthread_mutex_lock(&phi->godie_m);
	if (gettime(ft_read_llu(&phi->phi_m, &phi->tm_zero))
		- ft_read_llu(&phi->phi_m, &phi->last_eat)
		> (unsigned long long)ft_read_int(&dat->data_m, &dat->tm_die))
	{
		ft_print(phi, "died");
		ft_write_int(&dat->data_m, &dat->sig, SIG_END);
	}
	pthread_mutex_unlock(&phi->godie_m);
}

int	bigbrother(t_phi *now, t_dat *dat, int i)
{
	if (ft_read_int(&now->phi_m, &now->eat_ok) != EAT_OK
		&& ft_read_int(&now->phi_m, &now->eat_n)
		== ft_read_int(&dat->data_m, &dat->round))
	{
		i++;
		ft_write_int(&now->phi_m, &now->eat_ok, EAT_OK);
	}
	if (i == ft_read_int(&dat->data_m, &dat->nbr))
	{
		ft_write_int(&dat->data_m, &dat->sig, SIG_END);
		ft_write_int(&dat->data_m, &dat->sig_print, PRINT_KO);
	}
	return (i);
}

void	*routine_bigb(void *arg)
{
	t_dat	*dat;
	t_phi	*now;
	int		i;

	dat = (t_dat *)arg;
	now = dat->tail;
	i = 0;
	while (ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
	{
		now = now->next;
		if (ft_read_int(&dat->data_m, &dat->round) != -2)
			i = bigbrother(now, dat, i);
		go_die(now, dat);
	}
	return (NULL);
}

void	prec_sleep(unsigned long long delay, t_phi *phi)
{
	unsigned long long	final;

	final = gettime(ft_read_llu(&phi->dat->data_m, &phi->tm_zero)) + delay;
	while (gettime(ft_read_llu(&phi->dat->data_m, &phi->tm_zero)) < final)
		usleep(1000);
	return ;
}

unsigned long long	gettime(unsigned long long time_zero)
{
	struct timeval		current;
	unsigned long long	time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	if (time_zero > 0)
		time -= time_zero;
	return (time);
}
