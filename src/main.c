/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/06 17:40:04 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int ac, char **av)
{
	pthread_t	*thr;
	t_prg		*prg;
	int			i;
	int			*paco;

	if (ac < 5 && ac > 6)
		return (printf("Error"));
	prg = malloc(sizeof(t_prg));
	thr = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	paco = malloc(sizeof(int));
	if (!prg || !thr || !paco)
		return (0);
	ft_prg_init(prg, av);
	*paco = 666;
	i = -1;
	while (++i < prg->args->n_philos)
	{
		if (pthread_create(&thr[i], NULL, &ft_philos_routine,
				(void *)&prg->philo[i]))
			return (printf("Error creating threads."));
		usleep(100);
	}
	i = -1;
	while (++i < prg->args->n_philos)
	{
		if (pthread_join(thr[i], (void **)&paco))
			return (printf("Error ending threads."));
		if ((*paco))
		{
			printf("SA MATAO PACO	%i\n", prg->philo[i].id);
			return (0);
		}
	}
	return (0);
}

void	*ft_philos_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	//philo->actual_time = ft_actual_time();
	if (ft_philos_meal(philo))
		return ((void *)&philo->id);
	if (ft_philos_sleep(philo))
		return ((void *)&philo->id);
	if (ft_philos_think(philo))
		return ((void *)&philo->id);
	return (0);
}

int	ft_philos_meal(t_philo *philo)
{
	if (ft_philos_death(philo))
		return (philo->id);
	pthread_mutex_lock(&philo->forks_locker[(philo->id) - 1]);
	if (ft_philos_death(philo))
		return (philo->id);
	printf("%lums	%d	has taken a fork.\n",
		ft_elapse_time(philo), philo->id);
	pthread_mutex_lock(&philo->forks_locker[(philo->id)
		% philo->args->n_philos]);
	if (ft_philos_death(philo))
		return (philo->id);
	printf("%lums	%d	has taken a fork.\n", ft_elapse_time(philo), philo->id);
	printf("%lums	%d	is eating.\n", ft_elapse_time(philo), philo->id);
	usleep(philo->args->t_t_e * 1000);
	if (philo->args->n_t_m_e != -1)
		philo->ate++;
	philo->last_meal = ft_actual_time();
	pthread_mutex_unlock(&philo->forks_locker[(philo->id)
		% philo->args->n_philos]);
	pthread_mutex_unlock(&philo->forks_locker[(philo->id) - 1]);
	return (0);
}

int	ft_philos_sleep(t_philo *philo)
{
	if (ft_philos_death(philo))
		return (philo->id);
	printf("%lums	%d	is sleeping.\n", ft_elapse_time(philo), philo->id);
	usleep(philo->args->t_t_s * 1000);
	return (0);
}

int	ft_philos_think(t_philo *philo)
{
	if (ft_philos_death(philo))
		return (philo->id);
	printf("%lums	%d	is thinking.\n", ft_elapse_time(philo), philo->id);
	return (0);
}
	//Falta que se mueran los filósofos cuando no comen 
		//y que se acabe cuando hayan comido las veces que deban.
	//Comer y pillar tenedores - line 49
	//Dormir - line 63
	//Pensar - line 65
