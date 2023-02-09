/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/09 16:47:52 by ytoro-mo         ###   ########.fr       */
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
	{
		ft_philos(prg->philo, -1);
	}
	else
		ft_is_dead(prg->philo);
	ft_philo_deleter(prg);
	return (0);
}
	//system("leaks -q philo");

void	ft_philos(t_philo	*philos, int i)
{
	if (++i < philos->args->n_philos)
	{
		philos->args->p_id[i] = fork();
		if (!philos->args->p_id[i])
			ft_philos_routine(&philos[i]);
		else
			ft_philos(philos, i);
			i = -1;
	}
	waitpid(philos->args->p_id[i], 0, 0);
}

void	ft_philos_routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->args->sema);
		ft_print(philo, "has taken a fork", 0);
		sem_wait(philo->args->sema);
		ft_print(philo, "has taken a fork", 0);
		ft_print(philo, "is eating", 0);
		philo->last_meal = ft_actual_time();
		usleep(philo->args->t_t_e * 1000);
		sem_post(philo->args->sema);
		sem_post(philo->args->sema);
		if (++philo->ate == philo->args->n_t_m_e)
			return ;
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
		if (ft_actual_time() - philo[i].last_meal
			>= (unsigned long)philo->args->t_t_d)
		{
			ft_print(&philo[i], "died", 1);
			ft_kill(&philo[i]);
			exit (1);
		}
		i = (i + 1) % philo->args->n_philos;
	}
	printf("ESTE PAPU ES EL PROCESO PADRE.\n");
}
/* 		if (ft_end_meal(philo, i))
			break ; */

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
