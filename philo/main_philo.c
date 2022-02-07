/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:37:57 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/07 14:52:45 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fork(t_phi *phi, t_dat *dat)
{
	pthread_mutex_lock(&phi->fork_m);
	ft_print(phi, "has taken a fork");
	if (read_val(&dat->data_m, &dat->nbr) == 1)
	{
		while (read_val(&dat->data_m, &dat->sig) != SIG_END)
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
	ft_print(phi, "is eating");
	write_val(&phi->phi_m, &phi->last_eat,
		gettime(read_val(&dat->data_m, &dat->tm_zero)));
	write_val(&phi->phi_m, &phi->count_eat, phi->count_eat + 1);
	write_val(&dat->data_m, &dat->half_eat, dat->half_eat + 1);
	prec_wait(read_val(&dat->data_m, &dat->tm_eat), dat);
	pthread_mutex_unlock(&phi->next->fork_m);
	pthread_mutex_unlock(&phi->fork_m);
}

void	*routine_phi(void *arg)
{
	t_phi	*phi;
	t_dat	*dat;

	phi = (t_phi *)arg;
	dat = phi->dat;
	read_val(&dat->start_m, &dat->sig);
	while (read_val(&dat->data_m, &dat->sig) != SIG_END)
	{
		if ((read_val(&dat->data_m, &dat->sig) == ODD
				&& read_val(&phi->phi_m, &phi->n) % 2 == 1)
			|| (read_val(&dat->data_m, &dat->sig) == EVEN
				&& read_val(&phi->phi_m, &phi->n) % 2 == 0))
		{
			if (ft_fork(phi, dat))
				return (NULL);
			ft_eat(phi, dat);
			ft_print(phi, "is sleeping");
			prec_wait(read_val(&dat->data_m, &dat->tm_sle), dat);
			ft_print(phi, "is thinking");
		}
	}
	return (NULL);
}

int	philo_thread(t_dat *dat)
{
	t_phi			*now;
	unsigned long	i;

	i = 0;
	now = dat->tail;
	if (dat->round == 0)
		dat->sig = SIG_END;
	if (pthread_create(&dat->man_th, NULL, &routine_man, (void *)dat))
		return (1);
	pthread_mutex_lock(&dat->start_m);
	while (i < dat->nbr)
	{
		now = now->next;
		if (pthread_create(&now->phi_th, NULL, &routine_phi, (void *)now))
			return (1);
		i++;
	}
	usleep(50000);
	write_val(&dat->data_m, &dat->tm_zero, gettime(0));
	pthread_mutex_unlock(&dat->start_m);
	if (pthread_create(&dat->big_th, NULL, &routine_big, (void *)dat))
		return (1);
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
		return (ft_end_thread(&dat, "Error: invalid thread\n"));
	ft_end_thread(&dat, NULL);
	return (0);
}
