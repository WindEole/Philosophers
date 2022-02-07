/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:50:30 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/07 13:47:05 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/////     THREAD MANAGER     /////

void	ft_omega_eat(t_dat *dat)
{
	pthread_mutex_lock(&dat->data_m);
	if ((dat->nbr % 2 == 0 && dat->half_eat == dat->nbr / 2)
		|| (dat->nbr % 2 == 1 && dat->half_eat == dat->nbr / 2 + 1
			&& dat->sig == ODD)
		|| (dat->nbr % 2 == 1 && dat->half_eat == dat->nbr / 2
			&& dat->sig == EVEN))
	{
		if (dat->sig == EVEN)
			dat->sig = ODD;
		else if (dat->sig == ODD)
			dat->sig = EVEN;
		dat->half_eat = 0;
	}
	pthread_mutex_unlock(&dat->data_m);
	return ;
}

void	*routine_man(void *arg)
{
	t_dat	*dat;

	dat = (t_dat *)arg;
	while (read_val(&dat->data_m, &dat->sig) != SIG_END)
	{
		if (read_val(&dat->data_m, &dat->half_eat)
			>= read_val(&dat->data_m, &dat->nbr) / 2)
			ft_omega_eat(dat);
		usleep(1000);
	}
	return (NULL);
}

/////     THREAD BIGBROTHER     /////

void	go_die(t_phi *phi, t_dat *dat)
{
	if (gettime(read_val(&dat->data_m, &dat->tm_zero))
		- read_val(&phi->phi_m, &phi->last_eat)
		> read_val(&dat->data_m, &dat->tm_die))
	{
		ft_print(phi, "died");
		write_val(&dat->data_m, &dat->sig, SIG_END);
	}
}

unsigned long	go_eat(t_phi *now, t_dat *dat, unsigned long i)
{
	if (read_val(&now->phi_m, &now->full_eat) != EAT_OK
		&& read_val(&now->phi_m, &now->count_eat)
		== read_val(&dat->data_m, &dat->round))
	{
		i++;
		write_val(&now->phi_m, &now->full_eat, EAT_OK);
	}
	if (i == read_val(&dat->data_m, &dat->nbr))
	{
		write_val(&dat->data_m, &dat->sig, SIG_END);
		write_val(&dat->data_m, &dat->print, PRINT_KO);
	}
	return (i);
}

void	*routine_big(void *arg)
{
	t_dat			*dat;
	t_phi			*now;
	unsigned long	i;

	dat = (t_dat *)arg;
	now = dat->tail;
	i = 0;
	while (read_val(&dat->data_m, &dat->sig) != SIG_END)
	{
		now = now->next;
		if (read_val(&dat->data_m, &dat->round) != ULONG_MAX)
			i = go_eat(now, dat, i);
		go_die(now, dat);
	}
	return (NULL);
}
