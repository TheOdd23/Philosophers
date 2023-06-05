/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 08:39:47 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/17 08:15:38 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philos *philo, int status, long long time)
{
	pthread_mutex_lock(&(philo->vars->msg));
	if (status == EAT)
		printf("%lld Philosophe %d is eating\n", philo->last_meal, philo->philo_id);
	else if (status == SLEEP)
		printf("%lld Philosophe %d is sleeping\n", time, philo->philo_id);
	if (status == THINK)
		printf("%lld Philosophe %d is thinking\n", time, philo->philo_id);
	if (status == LFORKED || status == RFORKED)
		printf("%lld Philosophe %d is taking a fork\n", time, philo->philo_id);
	if (status == DEAD)
		printf("%lld Philosophe %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&(philo->vars->msg));
}
/*Revoir pertinence ALIVE à chaque action*/
void	*routine(void *arg)
{
	t_philos	*philo;
	t_vars		*vars;

	philo = (t_philos *)arg;
	vars = philo->vars;
	if (philo->philo_id % 2 == 0)
		usleep(15000);
	while (vars->life_stat != DEAD)
	{
		if (philo->action == THINK && vars->life_stat == ALIVE
			&& philo->fullness_stat != ISFULL)
			take_forks(vars, philo, philo->philo_id - 1);
		else if (philo->action == FFORKED && vars->life_stat == ALIVE)
			go_eat(philo->vars, philo);
		else if (philo->action == EAT && vars->life_stat == ALIVE)
			go_to_sleep(vars, philo, philo->philo_id - 1);
		else if (philo->action == SLEEP && vars->life_stat == ALIVE)
		{
			philo->action = THINK;
			print_status(philo, THINK, get_time(vars));
		}
	}
	return (0);
}

int	check_death(t_vars *vars, t_philos *philo)
{
	int		i;

	i = 0;
	while (1)
	{
		if (get_time(vars) - philo[i].last_meal >= vars->time_to_die)
		{
			pthread_mutex_lock(&(philo[i].vars->death));
			vars->life_stat = DEAD;
			usleep(500);
			print_status(philo, DEAD, get_time(vars));
			pthread_mutex_unlock(&(philo[i].vars->death));
			return (1);
		}
		if (vars->nb_isfull == vars->nb_philos)
			return (1);
		i++;
		if (i == vars->nb_philos)
			i = 0;
	}
	return (0);
}

int	philo(t_vars *vars)
{
	int	i;

	i = -1;
	begin_time(vars);
	while (++i < vars->nb_philos)
		pthread_create(&vars->philos[i].t_id, NULL, &routine, &vars->philos[i]);
	if (check_death(vars, vars->philos) == 1)
		return (1);
	return (0);
}
