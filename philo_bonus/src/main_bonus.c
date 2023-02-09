/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/09 13:45:15 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

int	main(int ac, char **av)
{
	t_prg	*prg;
	int		p_id;

	if (ac < 5 || ac > 6)
		return (printf("Error: incorrect number of variables."));
	prg = malloc(sizeof(t_prg));
	if (!prg)
		return (printf("Error allocating memory."));
	if (ft_prg_init(prg, av))
		return (printf("Error initializing variables."));
	p_id = fork();
	if (!p_id)
		ft_philos(prg->philo, -1);
	else
		ft_is_dead(prg->philo);
	waitpid(p_id, NULL, 0);
	ft_philo_deleter(prg);
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
/* 	int	i;

	i = 0;
	while (1)
	{
		if (ft_end_meal(philo, i))
			break ;
		if (ft_actual_time() - philo[i].last_meal
			>= (unsigned long)philo->args->t_t_d)
		{
			ft_print(&philo[i], "died", 1);
			return ;
		}
		i = (i + 1) % philo->args->n_philos;
	} */
	printf("ESTE PAPU ES EL PROCESO PADRE.\n");
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

void	ft_philos(t_philo	*philos, int i)
{
	int		p_id;

	if (++i < philos->args->n_philos)
	{
		p_id = fork();
		if (!p_id)
			printf ("PROCESO HIJO:	%i.\n", i);
		else
			ft_philos(philos, i);
	}
	waitpid(p_id, NULL, 0);
}
