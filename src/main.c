/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo <ytoro-mo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:54:00 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/05 20:00:36 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int ac, char **av)
{
	pthread_t	*thr;
	t_prg		*prg;
	int			i;

	if (ac < 5 && ac > 6)
		return (printf("Error"));
	prg = malloc(sizeof(t_prg));
	thr = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	if (!prg || !thr)
		return (0);
	ft_prg_init(prg, av);
	i = -1;
	while(++i < prg->args->n_philos)
	{
		if(pthread_create(&thr[i], NULL, &ft_philos_routine, (void*)&prg->philo[i]))
			return (printf("Error creating threads."));
		usleep(100);
	}
	i = -1;
	while(++i < prg->args->n_philos)
		if(pthread_join(thr[i], NULL))
			return (printf("Error ending threads."));
	return (0);
}

void	*ft_philos_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->actual_time = ft_actual_time();
	//Comer y pillar tenedores
	pthread_mutex_lock(&philo->forks_locker[(philo->id) - 1]);
	printf("%lums	%d	has taken a fork.\n", ft_elapse_time(philo), philo->id);
	pthread_mutex_lock(&philo->forks_locker[(philo->id) % philo->args->n_philos]);
 	printf("%lums	%d	has taken a fork.\n", ft_elapse_time(philo), philo->id);
	printf("%lums	%d	is eating.\n", ft_elapse_time(philo), philo->id);
	usleep(philo->args->t_t_e * 1000);
	if(philo->args->n_t_m_e != -1)
		philo->ate++;
    //sleep(2);
	pthread_mutex_unlock(&philo->forks_locker[(philo->id) % philo->args->n_philos]);
    pthread_mutex_unlock(&philo->forks_locker[(philo->id) - 1]);
		//Falta que se mueran los filósofos cuando no comen y que se acabe cuando hayan comido las veces que deban.
	//Dormir
	printf("%lums	%d	is sleeping.\n", ft_elapse_time(philo), philo->id);
	usleep(philo->args->t_t_s * 1000);
	//Pensar
	printf("%lums	%d	is thinking.\n", ft_elapse_time(philo), philo->id);
	return (0);
}
