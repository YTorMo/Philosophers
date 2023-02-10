/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:32:04 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/10 13:40:27 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

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
	ft_philos_init(prg->philo, prg->args);
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
	sem_unlink("forks");
	args->sema = sem_open("forks", O_CREAT, 0700, args->n_philos);
	sem_unlink("printer");
	args->sema_print = sem_open("printer", O_CREAT, 0700, 1);
}

void	ft_philos_init(t_philo *philos, t_prg_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
	{
		philos[i].ate = 0;
		philos[i].end_ate = 0;
		philos[i].dead = 0;
		philos[i].id = i + 1;
		philos[i].args = args;
		philos[i].init_time = ft_actual_time();
		philos[i].last_meal = ft_actual_time();
	}
}

void	ft_philo_deleter(t_prg *p)
{
	sem_close(p->args->sema);
	sem_unlink("forks");
	sem_close(p->args->sema_print);
	sem_unlink("printer");
	free(p->args);
	free(p->philo);
	free(p);
}
