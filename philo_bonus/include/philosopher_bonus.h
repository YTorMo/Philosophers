/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoro-mo < ytoro-mo@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:53:45 by ytoro-mo          #+#    #+#             */
/*   Updated: 2023/02/10 13:39:09 by ytoro-mo         ###   ########.fr       */
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
	sem_t			*sema;
	sem_t			*sema_print;
}t_prg_args;

typedef struct s_philo
{
	int				ate;
	int				end_ate;
	int				dead;
	int				id;
	t_prg_args		*args;
	unsigned long	init_time;
	unsigned long	last_meal;
}t_philo;

typedef struct s_main_program
{
	t_prg_args	*args;
	t_philo		*philo;
}t_prg;

int				ft_atoi(char *str);
void			ft_args_init(t_prg_args	*args, char **av);
void			ft_philos_init(t_philo *philos, t_prg_args	*args);
unsigned long	ft_elapse_time(t_philo	*philos);
unsigned long	ft_actual_time(void);
void			ft_philos_routine(t_philo *philo);
int				ft_prg_init(t_prg *prg, char **av);
void			ft_is_dead(t_philo *philo, int *p_id);
void			ft_philo_deleter(t_prg *p);
void			ft_print(t_philo *philo, char *text, int dead);
void			ft_philos(t_philo	*philos, int i);
int				ft_create_philos(t_philo	*philos, int	*p_id);
void			ft_philo_is_end(void *p);

#endif