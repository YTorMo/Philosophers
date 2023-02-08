/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/08 16:55:02 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

int	main(int ac, char **av)
{
	pthread_t		*thr;
	t_prg			*prg;
	int				i;

	if (ac < 5 && ac > 6)
		return (printf("Error"));
	prg = malloc(sizeof(t_prg));
	thr = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	if (!prg || !thr)
		return (printf("Error allocating memory."));
	ft_prg_init(prg, av);
	i = -1;
	while (++i < prg->args->n_philos)
	{
		if (pthread_create(&thr[i], NULL, &ft_philos_routine,
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
	while (1)
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
		if (philo->args->n_t_m_e != -1)
			if (++philo->ate == philo->args->n_t_m_e)
				break ;
		ft_print(philo, "is sleeping", 0);
		usleep(philo->args->t_t_s * 1000);
		ft_print(philo, "is thinking", 0);
	}
}

void	ft_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_end_meal(philo, i))
			break ;
		if (ft_actual_time() - philo[i].last_meal >= philo->args->t_t_d)
		{
			ft_print(&philo[i], "died", 1);
			return ;
		}
		i = (i + 1) % philo->args->n_philos;
	}
}

int	ft_end_meal(t_philo *philo, int i)
{
	int	j;
	int	e;

	if (philo[i].ate == philo->args->n_t_m_e)
		philo[i].end_ate = 1;
	j = -1;
	e = 0;
	while (++j < philo->args->n_philos)
		if (philo[j].end_ate == 0)
			e = 1;
	if (e == 0)
	{
		ft_print(&philo[i], "Termino de comer", 2);
		return (1);
	}
	return (0);
}
