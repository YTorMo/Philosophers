/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/07 12:24:10 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int ac, char **av)
{
	pthread_t		*thr;
	t_prg			*prg;
	int				i;
	int				*j;
	unsigned long	i_time;

	if (ac < 5 && ac > 6)
		return (printf("Error"));
	prg = malloc(sizeof(t_prg));
	thr = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	j = malloc(sizeof(int));
	if (!prg || !thr || !j)
		return (printf("Error allocating memory."));
	ft_prg_init(prg, av);
	i_time = ft_actual_time();
	i = -1;
	while (++i < prg->args->n_philos)
	{
		if (pthread_create(&thr[i], NULL, &ft_philos_routine,
				(void *)&prg->philo[i]))
			return (printf("Error creating threads."));
		usleep(100);
	}
	ft_is_dead(prg->philo);
	return (0);
}

void	*ft_philos_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		ft_philos_meal(philo);
		ft_philos_sleep(philo);
		ft_philos_think(philo);
	}
	return (NULL);
}

int	ft_philos_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks_locker[(philo->id) - 1]);
	printf("%lums	%d	has taken a fork.\n",
		ft_elapse_time(philo), philo->id);
	pthread_mutex_lock(&philo->forks_locker[(philo->id)
		% philo->args->n_philos]);
	printf("%lums	%d	has taken a fork.\n", ft_elapse_time(philo), philo->id);
	printf("%lums	%d	is eating.\n", ft_elapse_time(philo), philo->id);
	philo->last_meal = ft_actual_time();
	usleep(philo->args->t_t_e * 1000);
	if (philo->args->n_t_m_e != -1)
		philo->ate++;
	pthread_mutex_unlock(&philo->forks_locker[(philo->id)
		% philo->args->n_philos]);
	pthread_mutex_unlock(&philo->forks_locker[(philo->id) - 1]);
	return (0);
}

int	ft_philos_sleep(t_philo *philo)
{
	printf("%lums	%d	is sleeping.\n", ft_elapse_time(philo), philo->id);
	usleep(philo->args->t_t_s * 1000);
	return (0);
}

int	ft_philos_think(t_philo *philo)
{
	printf("%lums	%d	is thinking.\n", ft_elapse_time(philo), philo->id);
	return (0);
}
	//Falta que se mueran los filósofos cuando no comen 
		//y que se acabe cuando hayan comido las veces que deban.
	//Comer y pillar tenedores - line 49
	//Dormir - line 63
	//Pensar - line 65
