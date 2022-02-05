/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:03:36 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/05 08:13:15 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fork(t_phi *phi, t_dat *dat)
{
	pthread_mutex_lock(&phi->fork_m);
	ft_print(phi, "has taken a fork");
	if (ft_read_int(&dat->data_m, &dat->nbr) == 1)
	{
		while (ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
			usleep(500);
		pthread_mutex_unlock(&phi->fork_m);
		return (1);
	}
	pthread_mutex_lock(&phi->next->fork_m);
	ft_print(phi, "has taken a fork");
	return (0);
}

void	ft_eat(t_phi *phi, t_dat *dat)
{
	pthread_mutex_lock(&phi->busy_m);
	ft_print(phi, "is eating");
	ft_write_llu(&phi->phi_m, &phi->last_eat,
		gettime(ft_read_llu(&phi->phi_m, &phi->tm_zero)));
	ft_write_int(&phi->phi_m, &phi->eat_n, phi->eat_n + 1);
	ft_write_int(&dat->eat_m, &dat->sig_eat,
		ft_read_int(&dat->eat_m, &dat->sig_eat) + 1);
	prec_sleep(ft_read_int(&dat->data_m, &dat->tm_eat), phi);
	pthread_mutex_unlock(&phi->busy_m);
	pthread_mutex_unlock(&phi->fork_m);
	pthread_mutex_unlock(&phi->next->fork_m);
}

void	*routine_phi(void *arg)
{
	t_phi	*phi;
	t_dat	*dat;

	phi = (t_phi *)arg;
	dat = phi->dat;
	while (ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
	{
		if ((ft_read_int(&dat->data_m, &dat->sig) == ODD
				&& ft_read_int(&phi->phi_m, &phi->n) % 2 == 1)
			|| (ft_read_int(&dat->data_m, &dat->sig) == EVEN
				&& ft_read_int(&phi->phi_m, &phi->n) % 2 == 0))
		{
			if (ft_fork(phi, dat))
				return (NULL);
			ft_eat(phi, dat);
			ft_print(phi, "is sleeping");
			prec_sleep(ft_read_int(&dat->data_m, &dat->tm_sle), phi);
			ft_print(phi, "is thinking");
		}
	}
	return (NULL);
}
