/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:59:17 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/05 10:56:59 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_add_elem(t_dat *dat, int i)
{
	t_phi	*phi;

	phi = malloc(sizeof(*phi));
	if (phi == NULL)
		return (1);
	phi->n = i;
	phi->dat = dat;
	if (i == 1)
	{
		dat->head = phi;
		dat->tail = phi;
		phi->next = phi;
	}
	else
	{
		phi->next = dat->head;
		dat->tail->next = phi;
		dat->tail = phi;
	}
	return (0);
}

int	ft_init_phi(t_dat *dat)
{
	int	i;

	i = 1;
	dat->head = NULL;
	dat->tail = NULL;
	while (i <= dat->nbr)
	{
		if (ft_add_elem(dat, i))
			return (1);
		pthread_mutex_init(&dat->tail->fork_m, NULL);
		pthread_mutex_init(&dat->tail->phi_m, NULL);
		pthread_mutex_init(&dat->tail->godie_m, NULL);
		pthread_mutex_init(&dat->tail->busy_m, NULL);
		dat->tail->last_eat = 0;
		dat->tail->eat_n = 0;
		dat->tail->eat_ok = 0;
		i++;
	}
	return (0);
}

long	ft_atoi(const char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (s[i] == '+')
		i++;
	while (s[i] && (unsigned char)s[i] >= 48 && (unsigned char)s[i] <= 57)
	{
		res = (res * 10) + ((unsigned char)s[i] - 48);
		i++;
	}
	if (i == 0 || s[i] != '\0' || res > INT_MAX || i > 11)
		return (-1);
	return ((int)res);
}

int	ft_check_arg(int ac, char **av, t_dat *dat)
{
	if (ac != 5 && ac != 6)
		return (1);
	dat->nbr = ft_atoi(av[1]);
	dat->tm_die = ft_atoi(av[2]);
	dat->tm_eat = ft_atoi(av[3]);
	dat->tm_sle = ft_atoi(av[4]);
	if (ac == 6)
		dat->round = ft_atoi(av[5]);
	else
		dat->round = -2;
	if (dat->nbr <= 0 || dat->tm_die == -1 || dat->tm_eat == -1
		|| dat->tm_sle == -1 || dat->round == 0 || dat->round == -1)
		return (1);
	pthread_mutex_init(&dat->print_m, NULL);
	pthread_mutex_init(&dat->data_m, NULL);
	pthread_mutex_init(&dat->eat_m, NULL);
	dat->sig_print = PRINT_OK;
	dat->sig_eat = 0;
	dat->sig = ODD;
	return (0);
}
