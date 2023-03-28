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

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define ALIVE 5
# define LFORKED 6
# define RFORKED 7
# define FFORKED 10
# define UFORKED 11
# define ISFULL 8
# define NOTFULL 9

typedef struct s_vars	t_vars;

/* n_t_e = nb_time_ate */
/* l_t_e = last_time_eat */
/* t_id = thread_id */
/* fdstat = status fourchette droite */
/* fgstat = status fourchette gauche */
/* estat = Eat statut : full || not full */
typedef struct s_philos
{
	int				philo;
	int				stat;
	int				fdstat;
	int				fgstat;
	int				n_t_e;
	int				estat;
	long long		l_t_e;
	pthread_t		t_id;
	t_vars			*vars;
}	t_philos;

/* l_stat = life_status */
/* ttd = time to die */
/* tte = time to eat */
/* tts = time to sleep */
/* c_time = current time */
/* b_time = begin time */
/* nb_tte = number of time to eat */
typedef struct s_vars
{
	int				l_stat;
	int				nb_philos;
	long long		ttd;
	long long		tte;
	long long		tts;
	int				nb_isfull;
	int				nb_tte;
	long long		c_time;
	long long		b_time;
	pthread_mutex_t	death;
	pthread_mutex_t	msg;
	pthread_mutex_t	*forks;
	t_philos		*philos;
}	t_vars;

int			ft_atoi(const char *str);
int			ft_is_digit(int c);
int			philo(t_vars *vars);
long long	ft_get_time(t_vars *vars);
void		ft_begin_time(t_vars *vars);
void		take_forks(t_vars *vars, t_philos *philo, int i);
void		go_eat(t_vars *vars, t_philos *philo);
void		go_to_sleep(t_vars *vars, t_philos *philo, int i);
void		print_status(t_philos *philo, int status, long long time);
void		intellisleep(long long timetosleep, t_vars *vars);

#endif