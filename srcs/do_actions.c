/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:03:22 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/17 08:16:05 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	go_eat(t_vars *vars, t_philos *philo)
{
	philo->last_meal = get_time(vars);
	if (vars->nb_time_to_eat != -1)
	{
		philo->nb_meal++;
		if (philo->nb_meal == vars->nb_time_to_eat)
		{
			philo->fullness_stat = ISFULL;
			vars->nb_isfull++;
		}
	}
	philo->action = EAT;
	print_status(philo, EAT, get_time(vars));
	intellisleep(vars->time_to_eat, vars);
	return ;
}

void	go_to_sleep(t_vars *vars, t_philos *philo, int id)
{
	philo->action = SLEEP;
	philo->right_fork_stat = UFORKED;
	philo->left_fork_stat = UFORKED;
	pthread_mutex_unlock(&(vars->forks[id]));
	if (philo->philo == vars->nb_philos)
		pthread_mutex_unlock(&(vars->forks[0]));
	else
		pthread_mutex_unlock(&(vars->forks[id + 1]));
	print_status(philo, SLEEP, get_time(vars));
	intellisleep(vars->time_to_sleep, vars);
	return ;
}

void	take_forks(t_vars *vars, t_philos *philo, int id)
{
	pthread_mutex_lock(&(vars->forks[id]));
	philo->right_fork_stat = RFORKED;
	print_status(philo, RFORKED, get_time(vars));
	if (philo->philo == vars->nb_philos)
	{
		pthread_mutex_lock(&(vars->forks[0]));
		philo->left_fork_stat = LFORKED;
		print_status(philo, LFORKED, get_time(vars));
	}
	else
	{
		pthread_mutex_lock(&(vars->forks[id + 1]));
		philo->left_fork_stat = LFORKED;
		print_status(philo, LFORKED, get_time(vars));
	}
	if (philo->left_fork_stat == LFORKED && philo->right_fork_stat == RFORKED)
		philo->action = FFORKED;
}
