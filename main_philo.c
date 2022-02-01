/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:37:57 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/01 22:44:50 by iderighe         ###   ########.fr       */
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

void	*bigbrother(void *arg)
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
		{
			if (ft_read_int(&now->phi_m, &now->eat_ok) != EAT_OK
				&& ft_read_int(&now->phi_m, &now->eat_n)
				== ft_read_int(&dat->data_m, &dat->round))
			{
				i++;
				ft_write_int(&now->phi_m, &now->eat_ok, EAT_OK);
			}
			if (i == ft_read_int(&dat->data_m, &dat->nbr))
				ft_write_int(&dat->data_m, &dat->sig, SIG_END);
		}
		go_die(now, dat);
	}
	return (NULL);
}
/*
void	*routine_manager(void *arg)
{
	t_dat	*dat;
	
	dat = (t_dat *)arg;
	return (NULL);
}*/

void	ft_rootyne(t_phi *phi)
{
	t_dat	*dat;

	dat = phi->dat;
	pthread_mutex_lock(&phi->fork_m);
	ft_print(phi, "has taken a fork");
	if (ft_read_int(&dat->data_m, &dat->nbr) == 1)
	{
		while (ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
			usleep(500);
		pthread_mutex_unlock(&phi->fork_m);
		return ;
	}
	pthread_mutex_lock(&phi->next->fork_m);
	ft_print(phi, "has taken a fork");
	ft_print(phi, "is eating");
	ft_write_llu(&phi->phi_m, &phi->last_eat,
		gettime(ft_read_llu(&phi->phi_m, &phi->tm_zero)));
	ft_write_int(&phi->phi_m, &phi->eat_n, phi->eat_n + 1);
	ft_write_int(&dat->eat_m, &dat->sig_eat,
		ft_read_int(&dat->eat_m, &dat->sig_eat) + 1);
	usleep(ft_read_int(&dat->data_m, &dat->tm_eat) * 1000);
	pthread_mutex_unlock(&phi->next->fork_m);
	pthread_mutex_unlock(&phi->fork_m);
	ft_print(phi, "is sleeping");
	usleep(ft_read_int(&dat->data_m, &dat->tm_sle) * 1000);
	ft_print(phi, "is thinking");
}

void	*routine_phi(void *arg)
{
	t_phi	*phi;
	t_dat	*dat;

	phi = (t_phi *)arg;
	dat = phi->dat;
	if (phi->n % 2 == 0)
		usleep(dat->tm_eat * 1000);
	while (ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
	{
		ft_rootyne(phi);
	}
	return (arg);
}

int	philo_thread(t_dat *dat)
{
	t_phi	*now;
	int		i;

	i = 0;
	now = dat->tail;
//	if (pthread_create(&dat->eat_th, NULL, &routine_manager, (void *)dat))
//		return (1);
	while (i < dat->nbr)
	{
		now = now->next;
		now->tm_zero = gettime_zero();
		if (pthread_create(&now->phi_th, NULL, &routine_phi, (void *)now) != 0)
			return (1);
		i++;
	}
	pthread_create(&dat->die_th, NULL, &bigbrother, (void *)dat);
	return (0);
}

int	main(int ac, char **av)
{
	t_dat	dat;

	if (ft_check_arg(ac, av, &dat))
		return (ft_free_all(NULL, "Error: invalid parameters\n"));
	if (ft_init_phi(&dat))
		return (ft_free_all(&dat, "Error: liste chainee error\n"));
	if (philo_thread(&dat))
		return (ft_free_all(&dat, "Error: philo thread\n"));
	while (ft_read_int(&dat.data_m, &dat.sig) != SIG_END)
		usleep(500);
	ft_end_thread(&dat);
	return (0);
}
