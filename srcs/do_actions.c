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
	philo->l_t_e = ft_get_time(vars);
	if (vars->nb_tte != -1)
	{
		philo->n_t_e++;
		if (philo->n_t_e == vars->nb_tte)
		{
			philo->estat = ISFULL;
			vars->nb_isfull++;
		}
	}
	philo->stat = EAT;
	print_status(philo, EAT, ft_get_time(vars));
	intellisleep(vars->tte, vars);
	return ;
}

void	go_to_sleep(t_vars *vars, t_philos *philo, int i)
{
	philo->stat = SLEEP;
	philo->fdstat = UFORKED;
	philo->fgstat = UFORKED;
	pthread_mutex_unlock(&(vars->forks[i]));
	if (philo->philo == vars->nb_philos)
		pthread_mutex_unlock(&(vars->forks[0]));
	else
		pthread_mutex_unlock(&(vars->forks[i + 1]));
	print_status(philo, SLEEP, ft_get_time(vars));
	intellisleep(vars->tts, vars);
	return ;
}

void	take_forks(t_vars *vars, t_philos *philo, int i)
{
	pthread_mutex_lock(&(vars->forks[i]));
	philo->fdstat = RFORKED;
	print_status(philo, RFORKED, ft_get_time(vars));
	if (philo->philo == vars->nb_philos)
	{
		pthread_mutex_lock(&(vars->forks[0]));
		philo->fgstat = LFORKED;
		print_status(philo, LFORKED, ft_get_time(vars));
	}
	else
	{
		pthread_mutex_lock(&(vars->forks[i + 1]));
		philo->fgstat = LFORKED;
		print_status(philo, LFORKED, ft_get_time(vars));
	}
	if (philo->fgstat == LFORKED && philo->fdstat == RFORKED)
		philo->stat = FFORKED;
}
