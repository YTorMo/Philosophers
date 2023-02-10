/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/10 13:44:36 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

int	main(int ac, char **av)
{
	t_prg	*prg;
	int		*p_id;

	if (ac < 5 || ac > 6)
		return (printf("Error: incorrect number of variables."));
	prg = malloc(sizeof(t_prg));
	p_id = malloc(sizeof(int) * ft_atoi(av[1]));
	if (!prg || !p_id)
		return (printf("Error allocating memory."));
	if (ft_prg_init(prg, av))
		return (printf("Error initializing variables."));
	ft_create_philos(prg->philo, p_id);
	ft_is_dead(prg->philo, p_id);
	ft_philo_deleter(prg);
	return (0);
}
	//system("leaks -q philo");

void	ft_is_dead(t_philo *philo, int *p_id)
{
	int	i;
	int	status;

	i = -1;
	while (++i < philo->args->n_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->args->n_philos)
				kill(p_id[i], SIGINT);
		}
	}
}
