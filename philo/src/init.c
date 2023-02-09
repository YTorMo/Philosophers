/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:32:04 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/09 10:31:27 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_prg_init(t_prg *prg, char **av)
{
	t_prg_args	*args;
	t_philo		*philos;

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
	return (0);
}

void	ft_args_init(t_prg_args	*args, char **av)
{
	args->n_philos = ft_atoi(av[1]);
	args->t_t_d = ft_atoi(av[2]);
	args->t_t_e = ft_atoi(av[3]);
	args->t_t_s = ft_atoi(av[4]);
	if (av[5])
		args->n_t_m_e = ft_atoi(av[5]);
	else
		args->n_t_m_e = -1;
}

//No more data race. =D
void	init_lockers(t_prg *prg)
{
	pthread_mutex_t	*fork_locker;
	pthread_mutex_t	*print_locker;
	int				i;

	fork_locker = malloc(sizeof(pthread_mutex_t) * prg->args->n_philos);
	print_locker = malloc(sizeof(pthread_mutex_t));
	if (!fork_locker || !print_locker)
		return ;
	i = -1;
	while (++i < prg->args->n_philos)
		if (pthread_mutex_init(&fork_locker[i], NULL))
			return ;
	if (pthread_mutex_init(&(*print_locker), NULL))
		return ;
	ft_philos_init(prg->philo, prg->args, fork_locker, print_locker);
}

void	ft_philos_init(t_philo *philos, t_prg_args *args,
	pthread_mutex_t	*fork_locker, pthread_mutex_t *print_locker)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
	{
		philos[i].ate = 0;
		philos[i].end_ate = 0;
		philos[i].id = i + 1;
		philos[i].args = args;
		philos[i].forks_locker = fork_locker;
		philos[i].init_time = ft_actual_time();
		philos[i].last_meal = ft_actual_time();
		philos[i].print_locker = print_locker;
	}
}

void	ft_philo_deleter(t_prg *p)
{
	while (--(p->args->n_philos) > -1)
		pthread_mutex_destroy(&p->philo->forks_locker[p->args->n_philos]);
	pthread_mutex_destroy(&(*p->philo->print_locker));
	free(p->philo->forks_locker);
	free(p->philo->print_locker);
	free(p->args);
	free(p->philo);
	free(p);
}
