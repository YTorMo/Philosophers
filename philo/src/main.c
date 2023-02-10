/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/10 17:35:12 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int ac, char **av)
{
	pthread_t		*thr;
	t_prg			*prg;
	int				i;

	if (ft_check_input(ac, av))
		return (0);
	prg = malloc(sizeof(t_prg));
	thr = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	if (!prg || !thr)
		return (printf("Error allocating memory."));
	ft_prg_init(prg, av);
	i = -1;
	while (++i < prg->args->n_philos)
	{
		if (pthread_create(&thr[i], NULL, (void *)&ft_philos_routine,
				(void *)&prg->philo[i]))
			return (printf("Error creating threads."));
		usleep(100);
	}
	ft_is_dead(prg->philo);
	ft_philo_deleter(prg);
	free(thr);
	return (0);
}
	//system("leaks -q philo");

void	ft_philos_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->ate != philo->args->n_t_m_e && !philo->args->dead)
	{
		pthread_mutex_lock(&philo->forks_locker[(philo->id) - 1]);
		ft_print(philo, "has taken a fork", 0);
		pthread_mutex_lock(&philo->forks_locker[(philo->id)
			% philo->args->n_philos]);
		ft_print(philo, "has taken a fork", 0);
		ft_print(philo, "is eating", 0);
		philo->last_meal = ft_actual_time();
		usleep(philo->args->t_t_e * 1000);
		pthread_mutex_unlock(&philo->forks_locker[(philo->id)
			% philo->args->n_philos]);
		pthread_mutex_unlock(&philo->forks_locker[(philo->id) - 1]);
		if (++philo->ate != philo->args->n_t_m_e && !philo->args->dead)
		{
			ft_print(philo, "is sleeping", 0);
			usleep(philo->args->t_t_s * 1000);
			ft_print(philo, "is thinking", 0);
		}
		else if (philo->ate == philo->args->n_t_m_e)
			philo->args->end_ate++;
	}
}

void	ft_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_actual_time() - philo[i].last_meal
			>= (unsigned long)philo->args->t_t_d)
		{
			philo->args->dead = 1;
			ft_print(&philo[i], "died", 1);
			return ;
		}
		if (philo->args->end_ate == philo->args->n_philos)
		{
			ft_print(&philo[i], "died", 2);
			return ;
		}
		i = (i + 1) % philo->args->n_philos;
	}
}
