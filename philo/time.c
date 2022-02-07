/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:09:01 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/07 13:46:21 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prec_wait(unsigned long delay, t_dat *dat)
{
	unsigned long	final;

	final = gettime(read_val(&dat->data_m, &dat->tm_zero)) + delay;
	while (read_val(&dat->data_m, &dat->sig) != SIG_END
		&& gettime(read_val(&dat->data_m, &dat->tm_zero)) < final)
		usleep(1000);
	return ;
}

unsigned long	gettime(unsigned long time_zero)
{
	struct timeval	current;
	unsigned long	time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	if (time_zero > 0)
		time -= time_zero;
	return (time);
}
