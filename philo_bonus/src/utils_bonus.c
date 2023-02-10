/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:27:05 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/10 15:54:47 by ytoro-mo         ###   ########.fr       */
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
	sem_wait(philo->args->sema_print);
	if (dead != 2)
		printf("%lums	%d	%s.\n", ft_elapse_time(philo), philo->id, text);
	if (dead == 1 || dead == 2)
		return ;
	sem_post(philo->args->sema_print);
}

int	ft_atoi(char *str)
{
	long	n;
	int		s;

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
	if (n > INT32_MAX)
		return (0);
	return (s * (int)n);
}

int	ft_check_input(int ac, char **av)
{
	if (ac < 5 || ac > 6 || ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (printf("Error: icorrect input.\n"));
	if (av[5] != NULL)
		if (ft_atoi(av[5]) <= 0)
			return (printf("Error: icorrect input.\n"));
	return (0);
}
