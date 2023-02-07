/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:27:05 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/07 12:27:16 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

unsigned long	ft_actual_time(void)
{
	struct timeval	time;
	unsigned long	ret;

	gettimeofday(&time, NULL);
	ret = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (ret);
}

unsigned long	ft_elapse_time(t_philo	*philos)
{
	unsigned long	ret;

	ret = ft_actual_time() - philos->init_time;
	return (ret);
}

int	ft_atoi(char *str)
{
	int	n;
	int	s;

	s = 1;
	n = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + (*str - 48);
		str++;
	}
	return (s * n);
}

void	ft_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_actual_time() - philo[i].last_meal >= philo->args->t_t_d)
		{
			printf("%lums %i died.\n", ft_elapse_time(&philo[i]), philo[i].id);
			return ;
		}
		i = (i + 1) % philo->args->n_philos;
		usleep(100);
	}
}

//printf("%lums ultima comida de %i.\n", ft_actual_time() - philo[i].last_meal,
//i + 1);
/* int	ft_philos_ate(t_prg *prg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)prg->philo;
	i = -1;
	while (++i < prg->args->n_philos)
	{
		if (prg->args->n_t_m_e != philo[i].ate)
			return (0);
	}
	return (1);
} */
