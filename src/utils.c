/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:27:05 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/01/26 12:08:29 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

unsigned long	ft_actual_time(void)
{
	struct timeval	time;
	unsigned long	ret;

	printf("LLEGA HASTA AQUI	5,0!!!!!!!!!!\n");
	gettimeofday(&time, NULL);
	printf("LLEGA HASTA AQUI	5,1!!!!!!!!!!\n");
	ret = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	printf("LLEGA HASTA AQUI	5,2!!!!!!!!!!\n");
	return (ret);
}

unsigned long	ft_elapse_time(t_philo	*philos)
{
	unsigned long	ret;

	printf("LLEGA HASTA AQUI	6,0!!!!!!!!!!\n");
	ret = ft_actual_time() - philos->args->elapse_time;
	printf("LLEGA HASTA AQUI	6,1!!!!!!!!!!\n");
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
