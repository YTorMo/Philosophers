/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:53:45 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/08 16:55:56 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_prg_args
{
	int				n_philos;
	int				t_t_d;
	int				t_t_e;
	int				t_t_s;
	int				n_t_m_e;
	unsigned long	elapse_time;
}t_prg_args;

typedef struct s_philo
{
	int				ate;
	int				end_ate;
	int				id;
	t_prg_args		*args;
	unsigned long	init_time;
	unsigned long	last_meal;
	pthread_mutex_t	*forks_locker;
	pthread_mutex_t	*print_locker;
}t_philo;

typedef struct s_main_program
{
	t_prg_args	*args;
	t_philo		*philo;
}t_prg;

int				ft_atoi(char *str);
void			ft_args_init(t_prg_args	*args, char **av);
void			init_lockers(t_prg *prg);
void			ft_philos_init(t_philo *philos, t_prg_args	*args,
					pthread_mutex_t	*fork_locker,
					pthread_mutex_t *print_locker);
unsigned long	ft_elapse_time(t_philo	*philos);
unsigned long	ft_actual_time(void);
void			ft_philos_routine(void *p);
int				ft_prg_init(t_prg *prg, char **av);
void			ft_is_dead(t_philo *philo);
void			ft_philo_deleter(t_prg *p);
void			ft_print(t_philo *philo, char *text, int dead);
int				ft_end_meal(t_philo *philo, int i);

#endif