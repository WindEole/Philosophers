/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:44:15 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/01 22:39:36 by iderighe         ###   ########.fr       */
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

void	ft_end_thread(t_dat *dat)
{
	t_phi	*now;
	int		i;

//	pthread_join(dat->eat_th, NULL);
	pthread_join(dat->die_th, NULL);
	i = 0;
	now = dat->tail;
	while (i < dat->nbr)
	{
		now = now->next;
		pthread_join(now->phi_th, NULL);
////printf(CYAN"thread [%d] has finished execution"RESET"\n", i);
		i++;
	}
	pthread_mutex_destroy(&dat->eat_m);
	pthread_mutex_destroy(&dat->print_m);
	pthread_mutex_destroy(&dat->data_m);
	while (i < dat->nbr)
	{
		now = now->next;
		pthread_mutex_destroy(&now->phi_m);
		pthread_mutex_destroy(&now->fork_m);
		pthread_mutex_destroy(&now->godie_m);
		i++;
	}
	ft_free_all(dat, NULL);
}

unsigned long long	gettime_zero(void)
{
	struct timeval		current;
	unsigned long long	time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);
}

unsigned long long	gettime(unsigned long long time_zero)
{
	struct timeval		current;
	unsigned long long	time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000) - time_zero;
	return (time);
}

long	ft_atoi(const char *s)
{
	int		i;
	int		minus;
	long	res;

	i = 0;
	minus = 1;
	res = 0;
	while (s[i] == 32 || (s[i] > 8 && s[i] < 14))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			return (-1);
		i++;
	}
	while (s[i] && (unsigned char)s[i] >= 48 && (unsigned char)s[i] <= 57)
	{
		res = (res * 10) + ((unsigned char)s[i] - 48);
		i++;
	}
	if (res > INT_MAX)
		return (-1);
	return (res);
}
