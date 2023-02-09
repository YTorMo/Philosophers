/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:27:05 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/09 16:35:00 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

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

void	ft_print(t_philo *philo, char *text, int dead)
{
	if (dead != 2)
		printf("%lums	%d	%s.\n", ft_elapse_time(philo), philo->id, text);
	if (dead == 1 || dead == 2)
		return ;
}

void	ft_kill(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->args->n_philos)
		kill(philos->args->p_id[i], SIGINT);
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
//printf("%lums ultima comida de %i.\n", ft_actual_time()
// - philo[i].last_meal, i + 1);
