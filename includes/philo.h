/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 06:40:52 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/17 08:57:39 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define ALIVE 5
# define LFORKED 6
# define RFORKED 7
# define FFORKED 8
# define UFORKED 9
# define ISFULL 10
# define NOTFULL 11

typedef struct s_vars	t_vars;

typedef struct s_philos
{
	int				philo_id;
	int				action;
	int				right_fork_stat;
	int				left_fork_stat;
	int				nb_meal;
	int				fullness_stat;
	long long		last_meal;
	pthread_t		t_id;
	t_vars			*vars;
}	t_philos;

typedef struct s_vars
{
	int				life_stat;
	int				nb_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_isfull;
	int				nb_time_to_eat;
	long long		current_time;
	long long		beggining_time;
	pthread_mutex_t	death;
	pthread_mutex_t	msg;
	pthread_mutex_t	*forks;
	t_philos		*philos;
}	t_vars;

int			ft_atoi(const char *str);
int			ft_is_digit(int c);
int			philo(t_vars *vars);
long long	get_time(t_vars *vars);
void		begin_time(t_vars *vars);
void		take_forks(t_vars *vars, t_philos *philo, int i);
void		go_eat(t_vars *vars, t_philos *philo);
void		go_to_sleep(t_vars *vars, t_philos *philo, int i);
void		print_status(t_philos *philo, int status, long long time);
void		intellisleep(long long timetosleep, t_vars *vars);

#endif