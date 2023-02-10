/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:38:15 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/10 13:36:17 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

int	ft_create_philos(t_philo *philos, int *p_id)
{
	int	i;

	i = -1;
	while (++i < philos->args->n_philos)
	{
		p_id[i] = fork();
		if (p_id[i] == -1)
			exit(1);
		else if (!p_id[i])
		{
			ft_philos_routine(&philos[i]);
			exit (0);
		}
	}
	return (0);
}

void	ft_philos_routine(t_philo *philo)
{
	pthread_t		thr;

	if (pthread_create(&thr, NULL, (void *)&ft_philo_is_end, (void *)philo))
		exit (1);
	while (philo->ate != philo->args->n_t_m_e && !philo->dead)
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
		if (++philo->ate != philo->args->n_t_m_e && !philo->dead)
		{
			ft_print(philo, "is sleeping", 0);
			usleep(philo->args->t_t_s * 1000);
			ft_print(philo, "is thinking", 0);
		}
	}
	exit (0);
}

void	ft_philo_is_end(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!philo->dead)
	{
		if (ft_actual_time() - philo->last_meal
			>= (unsigned long)philo->args->t_t_d)
		{
			philo->dead = 1;
			ft_print(philo, "died", 1);
			exit (1);
		}
	}
}
