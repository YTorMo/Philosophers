/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:53:45 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/01/26 11:33:55 by ytoro-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_prg_args
{
	int				n_philos;
	int				*forks;
	int				t_t_d;
	int				t_t_e;
	int				t_t_s;
	int				n_t_m_e;
	int				death;
	unsigned long	elapse_time;
}t_prg_args;

typedef struct s_philo
{
	int				ate;
	int				id;
	int				fork;
	t_prg_args		*args;
	pthread_t		*thr_p;
	unsigned long	actual_time;
	pthread_mutex_t	forks_locker;
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
					pthread_mutex_t	fork_locker);
unsigned long	ft_elapse_time(t_philo	*philos);
unsigned long	ft_actual_time(void);
void			*ft_philos_task_manager(void *p);
void			*ft_philos_routine(void *p);
int				ft_philos_ate(t_prg *prg);
int				ft_prg_init(t_prg *prg, char **av);

#endif