/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CV10_cond_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:24:33 by iderighe          #+#    #+#             */
/*   Updated: 2022/01/21 18:29:43 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

/////// CV Condition variables in C, a 2 minutes //////

void	*r_fuel_fill(void *arg)
{

}

void	*r_car(void *arg)
{

}

int	main(int ac, char **av)
{
	pthread_t	th[2];
	int			i;

//	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 2)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &r_fuel_fill, NULL))
				return (1);
			printf(CYAN"Thread [%d] has started"RESET"\n", i);
		}
		else
		{
			if (pthread_create(&th[i], NULL, &r_car, NULL))
				return (1);
			printf(CYAN"Thread [%d] has started"RESET"\n", i);
		}
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (pthread_join(th[i], NULL))
			return (1);
		printf(BLUE"Thread [%d] has finished"RESET"\n", i);
		i++;
	}
//	pthread_mutex_destroy(&mutex);
	return (0);
}
