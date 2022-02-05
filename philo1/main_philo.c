/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:37:57 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/04 12:52:40 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_omega_eat(t_dat *dat)
{
	if ((ft_read_int(&dat->data_m, &dat->nbr) % 2 == 0
			&& ft_read_int(&dat->eat_m, &dat->sig_eat)
			== ft_read_int(&dat->eat_m, &dat->nbr) / 2)
		|| (ft_read_int(&dat->data_m, &dat->nbr) % 2 == 1
			&& ft_read_int(&dat->data_m, &dat->sig) == ODD
			&& ft_read_int(&dat->eat_m, &dat->sig_eat)
			== ft_read_int(&dat->eat_m, &dat->nbr) / 2 + 1)
		|| (ft_read_int(&dat->data_m, &dat->nbr) % 2 == 1
			&& ft_read_int(&dat->data_m, &dat->sig) == EVEN
			&& ft_read_int(&dat->eat_m, &dat->sig_eat)
			== ft_read_int(&dat->eat_m, &dat->nbr) / 2))
	{
		pthread_mutex_lock(&dat->data_m);
		if (dat->sig == EVEN)
			dat->sig = ODD;
		else if (dat->sig == ODD)
			dat->sig = EVEN;
		pthread_mutex_unlock(&dat->data_m);
		ft_write_int(&dat->eat_m, &dat->sig_eat, 0);
		return ;
	}
}

void	*routine_man(void *arg)
{
	t_dat	*dat;

	dat = (t_dat *)arg;
	while (ft_read_int(&dat->data_m, &dat->sig) != SIG_END)
	{
		if (ft_read_int(&dat->eat_m, &dat->sig_eat)
			>= ft_read_int(&dat->data_m, &dat->nbr) / 2)
			ft_omega_eat(dat);
		usleep(1000);
	}
	return (NULL);
}

int	philo_thread(t_dat *dat)
{
	t_phi	*now;
	int		i;

	i = 0;
	now = dat->tail;
	if (pthread_create(&dat->eat_th, NULL, &routine_man, (void *)dat))
		return (1);
	while (i < dat->nbr)
	{
		now = now->next;
		now->tm_zero = gettime(0);
		if (pthread_create(&now->phi_th, NULL, &routine_phi, (void *)now))
			return (1);
		i++;
	}
	if (pthread_create(&dat->die_th, NULL, &routine_bigb, (void *)dat))
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
	while (ft_read_int(&dat.data_m, &dat.sig) != SIG_END)
		usleep(500);
	ft_end_thread(&dat, NULL);
	return (0);
}
