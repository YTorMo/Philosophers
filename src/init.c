/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:32:04 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/01/26 12:10:58 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_prg_init(t_prg *prg, char **av)
{
	t_prg_args	*args;
	t_philo		*philos;
	int			i;

	args = malloc(sizeof(t_prg_args));
	if (!args)
		return (printf("Error init args.\n"));
	ft_args_init(args, av);
	prg->args = args;
	philos = malloc(sizeof(t_philo) * args->n_philos);
	if (!philos)
		return (printf("Error init philos.\n"));
	prg->philo = philos;
	init_lockers(prg);
	printf("LLEGA HASTA AQUI	1!!!!!!!!!!\n");
}

void	ft_args_init(t_prg_args	*args, char **av)
{
	int	i;

	args->n_philos = ft_atoi(av[1]);
	args->forks = malloc(sizeof(int) * args->n_philos);
	if (!args->forks)
		return ;
	i = -1;
	while (++i < args->n_philos)
		args->forks[i] = 1;
	args->t_t_d = ft_atoi(av[2]);
	args->t_t_e = ft_atoi(av[3]);
	args->t_t_s = ft_atoi(av[4]);
	if (av[5])
		args->n_t_m_e = ft_atoi(av[5]);
	else
		args->n_t_m_e = -1;
	args->death = 0;
	printf("LLEGA HASTA AQUI	2!!!!!!!!!!\n");
}

//No more data race. =D
void	init_lockers(t_prg *prg)
{
	pthread_mutex_t	fork_locker;

	if (pthread_mutex_init(&fork_locker, NULL))
		return ;
	ft_philos_init(prg->philo, prg->args, fork_locker);
	printf("LLEGA HASTA AQUI	3!!!!!!!!!!\n");
}

void	ft_philos_init(t_philo *philos, t_prg_args *args,
	pthread_mutex_t	fork_locker)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
	{
		philos[i].ate = 0;
		philos[i].id = i + 1;
		philos[i].args = args;
		philos[i].forks_locker = fork_locker;
		philos[i].actual_time = ft_actual_time();
	}
	printf("LLEGA HASTA AQUI	4!!!!!!!!!!\n");
}
		//printf("LLEGA HASTA AQUI!!!!!!!!!!\n");
