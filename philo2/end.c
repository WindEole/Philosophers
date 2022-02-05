/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:44:15 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/05 20:14:47 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_all(t_dat *dat, char *s)
{
	int		i;
	t_phi	*now;

	if (dat && dat->head)
	{
		while (dat->head != dat->tail)
		{
			now = dat->head;
			dat->head = now->next;
			free(now);
		}
		free(dat->head);
	}
	if (s)
	{
		i = -1;
		while (s[++i])
			write(2, &s[i], 1);
	}
	return (1);
}

int	ft_end_thread(t_dat *dat, char *s)
{
	t_phi			*now;
	unsigned long	i;

	pthread_join(dat->man_th, NULL);
	pthread_join(dat->big_th, NULL);
	i = -1;
	now = dat->tail;
	while (++i < dat->nbr)
	{
		now = now->next;
		pthread_join(now->phi_th, NULL);
	}
	pthread_mutex_destroy(&dat->data_m);
	pthread_mutex_destroy(&dat->print_m);
	pthread_mutex_destroy(&dat->start_m);
	i = -1;
	while (++i < dat->nbr)
	{
		now = now->next;
		pthread_mutex_destroy(&now->phi_m);
		pthread_mutex_destroy(&now->fork_m);
	}
	return (ft_free_all(dat, s));
}
