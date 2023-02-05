/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo <ytoro-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:32:04 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/05 18:00:23 by ytoro-mo         ###   ########.fr       */
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
}

void	ft_args_init(t_prg_args	*args, char **av)
{
	int	i;

	args->n_philos = ft_atoi(av[1]);
	args->t_t_d = ft_atoi(av[2]);
	args->t_t_e = ft_atoi(av[3]);
	args->t_t_s = ft_atoi(av[4]);
	if (av[5])
		args->n_t_m_e = ft_atoi(av[5]);
	else
		args->n_t_m_e = -1;
	args->death = 0;
}

//No more data race. =D
void	init_lockers(t_prg *prg)
{
	pthread_mutex_t	*fork_locker;
	int i;

    fork_locker = malloc(sizeof(pthread_mutex_t) * prg->args->n_philos);
	i = -1;
	while (++i < prg->args->n_philos)
		if (pthread_mutex_init(&fork_locker[i], NULL))
			return ;
	ft_philos_init(prg->philo, prg->args, fork_locker);
}

void	ft_philos_init(t_philo *philos, t_prg_args *args,
	pthread_mutex_t	*fork_locker)
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
}
		//printf("LLEGA HASTA AQUI!!!!!!!!!!\n");
