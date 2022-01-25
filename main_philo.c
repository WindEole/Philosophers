/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:37:57 by iderighe          #+#    #+#             */
/*   Updated: 2022/01/25 18:09:52 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

//pthread_mutex_t	fork;
/*int	ft_error(char *s, int ret)
{
	int	i;

	i = -1;
	while (s[++i])
		write(1, &s[i], 1);
	return (ret);
}*/

int	ft_free_all(long *tab, t_dat *dat, char *s)
{
	int	i;

	if (tab)
		free(tab);
//	if (dat)
//		pthread_mutex_destroy(&dat->mutex);
	if (s)
	{
		i = -1;
		while (s[++i])
			write(2, &s[i], 1);
	}
	return (1);

}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atoi(const char *s)
{
	int			i;
	int			minus;
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

void	ft_add_elem(t_dat *dat, int i)
{
	t_phi	phi;

	phi.np = i;
	phi.nf = i;
	phi.dat = dat;
	if (i == 1)
	{
		dat->head = &phi;
		dat->tail = &phi;
		phi.next = &phi;
	}
	else
	{
		phi.next = dat->head;
		dat->tail->next = &phi;
		dat->tail = &phi;
	}
}

int	ft_init_phi(t_dat *dat)
{
	int	i;

	i = 1;
	while (i <= dat->npf)
	{
		ft_add_elem(dat, i);
		i++;
	}
	return (0);
}

void	ft_init_dat(int ac, char **av, t_dat *dat)
{
	dat->npf = ft_atoi(av[1]);
	if (dat->npf == 0)
		return ;
	dat->die = ft_atoi(av[2]);
	dat->eat = ft_atoi(av[3]);
	dat->sle = ft_atoi(av[4]);
	if (ac == 6)
		dat->t = ft_atoi(av[5]);
	else
		dat->t = 0;
printf(GREEN"npf = [%d]\nt_die = [%d]\nt_eat = [%d]\nt_sle = [%d]\ntours = [%d]"RESET"\n", dat->npf, dat->die, dat->eat, dat->sle, dat->t);
}

int	ft_check_arg(int ac, char **av, t_dat *dat)
{
	long	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(long) * (ac));
	if (tmp == NULL)
		return (1);
	i = 0;
	j = 1;
	while (j < ac)
	{
		tmp[i] = ft_atoi(av[j]);
		if (tmp[i] == -1)
			return (ft_free_all(tmp, NULL, NULL));
		i++;
		j++;
	}
	free(tmp);
	ft_init_dat(ac, av, dat);
	if (dat->npf == 0)
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	int	i;
	int	sum;

	i = 0;
	sum = *(int*)arg;
	while (i < 10000)
	{
		sum++;
//printf(CYAN"loop = [%d]"RESET"\n", sum);
		i++;
	}
//	int	fork = dat->npf;
//	int	*res = malloc(sizeof(int));

//	i = 0;
//	while (i < phi->n_phi && fork > 1)
//	while (fork > 1)
/*	if (fork > 1)
	{
		pthread_mutex_lock(&phi->mutex);
		printf(BLUE"nb de fourchettes disponibles = [%d]"RESET"\n", fork);
//		fork = fork - 2;
		if (usleep(phi->t_eat * 1000000) != 0)
			return (NULL);
		else
			fork = fork + 2;
		printf("ending\n");
		pthread_mutex_unlock(&phi->mutex);
//		i++;
	}*/
printf(CYAN"local sum = [%d]"RESET"\n", sum);
	*(int*)arg = sum;
	return (arg);
}

int	philo_thread(t_dat *dat)
{
	pthread_t	pt[dat->npf];
	int			*a;
	int			*r;
	int			i;
//	int			res;
	int	mail;

//	pthread_mutex_init(&phi->mutex, NULL);
//	res = 0;
	i = 0;
//	if (y)
	mail = 0;
	while (i < dat->npf)
	{
		a = malloc(sizeof(int));
		if (a == NULL)
			return (1);
		*a = mail;
		if (pthread_create(&pt[i], NULL, &routine, a) != 0)
//		if (pthread_create(&pt[i], NULL, &routine, NULL) != 0)
			return (1);
printf(YELLOW"thread [%d] has started"RESET"\n", i);
printf(RED"i = [%d]"RESET"\n", i);
		i++;
	}
	i = 0;
	while (i < dat->npf)
	{
		if (pthread_join(pt[i], (void **)&r))
//		if (pthread_join(pt[i], NULL))
			return (1);
printf(PURPLE"thread [%d] has finished execution"RESET"\n", i);
printf(RED"i = [%d]"RESET"\n", i);
		i++;
		mail += *r;
		free(r);
	}
printf(BLUE"mail = [%d]"RESET"\n", mail);
//	pthread_mutex_destroy(&dat->mutex);
//	printf("philo_thread result = [%d]\n", *r);
	return (0);
}

int	main(int ac, char **av)
{
	t_dat			dat;

	if (ac != 5 && ac != 6)
		return (ft_free_all(NULL, NULL, "Error: argument\n"));
	if (ft_check_arg(ac, av, &dat))
		return (ft_free_all(NULL, NULL, "Error: argument init_dat\n"));
	if (ft_init_phi(&dat));
//		return(ft_free_all(NULL, NULL, "Error: liste chainee error\n"));
	if (philo_thread(&dat))
		return (ft_free_all(NULL, &dat, "Error: cacaboudin\n"));
	return (0);
}
