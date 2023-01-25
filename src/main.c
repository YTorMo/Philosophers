/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/01/25 17:23:32 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*
** int	main(int ac, char **av)
** {
** 	pthread_t	*thr;
** 	t_prg		*prg;
** 	int			i;
** 
** 	printf("LLEGA");
** 	if (ac < 5 || ac > 6)
** 		return (0);
** 	prg = malloc(sizeof(t_prg *));
** 	if (!prg)
** 		return (0);
** 	ft_prg_init(prg, av);
** 	i = -1;
** 	while (!ft_philos_ate(prg) && !prg->args->death)
** 	{
** 		++i;
** 		if (pthread_create (&prg->philo[i].thr_p, NULL, ft_philos_task_manager,
** 				&prg->philo[i]))
** 		{
** 			printf("Thread for philo -%i- can not be created.", i);
** 			return (0);
** 		}
** 		if (i >= 3)
** 			i = -1;
** 	}
** 	//system("leaks -q philo");
** 	return (0);
** }
*/

/* void	*ft_philos_task_manager(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->actual_time = ft_actual_time();
	while (1)
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	}
	printf("Filosofo numero -%i-\n", philo->id);
	philo->ate++;
	printf("Filosofo numero -%i- ha comido %i veces\n", philo->id, philo->ate);
	return (0);
} */

int	main(int ac, char **av)
{
	pthread_t	*thr;
	t_prg		*prg;
	int			i;

	if (ac < 5 && ac > 6)
		return (printf("Error"));
	prg = malloc(sizeof(t_prg *));
	if (!prg)
		return (0);
	ft_prg_init(prg, av);
	printf("	%lums\n", ft_actual_time());
	return (0);
}

void	*ft_philos_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	//Comer y pillar tenedores
	printf("%lums	%d	has taken a fork.\n", ft_elapse_time(philo), philo->id);
	printf("%lums	%d	has taken a fork.\n", ft_elapse_time(philo), philo->id);
	printf("%lums	%d	is eating.\n", ft_elapse_time(philo), philo->id);
		//Falta incluir el número de veces que comen los jodios.
	usleep(philo->args->t_t_e * 1000);
	//Dormir
	printf("%lums	%d	is sleeping.\n", ft_elapse_time(philo), philo->id);
	usleep(philo->args->t_t_s * 1000);
	//Pensar
	printf("%lums	%d	is thinking.\n", ft_elapse_time(philo), philo->id);
	return (0);
}
