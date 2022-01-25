/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:39:31 by iderighe          #+#    #+#             */
/*   Updated: 2022/01/25 18:09:35 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> // memset
# include <unistd.h> // usleep
# include <sys/time.h> // gettimeofday
# include <stdlib.h> // malloc / free
# include <limits.h> // INT_MIN / INT_MAX
# include <stdio.h> // printf
# include <pthread.h> // thread functions !

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

typedef struct s_phi
{
	int		np;
	int		nf;
	struct s_dat	*dat;
	struct s_phi	*next;
}	t_phi;

typedef struct s_dat
{
	int		npf; // nb de philosophes et de fourchettes
	int		die; // (ms) time between last meal and death
	int		eat; // (ms) time it takes for a philosopher to eat
	int		sle; // (ms) time the philosophers sleeps
	int		t; // OPTIONAL nb de fois ou 1 philo doit manger)
	struct s_phi	*head;
	struct s_phi	*tail;

}	t_dat;


/*typedef struct s_phi
{
	int		np;
	int		nf;
	t_dat	*dat;
	t_phi	*next;
}	t_phi;*/


#endif
