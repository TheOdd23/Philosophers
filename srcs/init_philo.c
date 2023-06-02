/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 06:36:48 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/17 08:14:21 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_vars(t_vars *vars)
{
	int	i;

	i = -1;
	if (!vars->philos)
		return ;
	free (vars->philos);
	if (!vars->forks)
		return ;
	while (++i < vars->nb_philos)
		pthread_mutex_destroy(&(vars->forks[i]));
	free(vars->forks);
	pthread_mutex_destroy(&(vars->death));
	pthread_mutex_destroy(&(vars->msg));
}

int	set_philos(t_vars *vars)
{
	int	i;

	i = -1;
	vars->philos = malloc(sizeof(t_philos) * vars->nb_philos + 1);
	if (!vars->philos)
		return (1);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->nb_philos);
	if (!vars->forks)
		return (1);
	while (++i < vars->nb_philos)
	{
		vars->philos[i].last_meal = 0;
		vars->philos[i].philo_id = i + 1;
		vars->philos[i].nb_meal = 0;
		vars->philos[i].action = THINK;
		vars->philos[i].vars = vars;
		vars->philos[i].fullness_stat = NOTFULL;
		if (pthread_mutex_init(&(vars->msg), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(vars->death), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(vars->forks[i]), NULL) != 0)
			return (1);
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	ii;

	i = 0;
	while (++i < ac)
	{
		ii = -1;
		while (av[i][++ii])
		{
			if (ft_is_digit(av[i][ii]) == 0)
			{
				write(2, "Wrong argument\n", 16);
				return (1);
			}
		}
	}
	return (0);
}

int	set_variables(int ac, char **av, t_vars *vars)
{
	vars->nb_isfull = 0;
	vars->life_stat = ALIVE;
	vars->nb_philos = ft_atoi(av[1]);
	vars->time_to_die = ft_atoi(av[2]);
	vars->time_to_eat = ft_atoi(av[3]);
	vars->time_to_sleep = ft_atoi(av[4]);
	vars->nb_time_to_eat = -1;
	if (ac == 6)
	{
		vars->nb_time_to_eat = ft_atoi(av[5]);
		if (vars->nb_time_to_eat <= 0)
			return (1);
	}
	if (vars->nb_philos < 1 || vars->time_to_die < 0 || vars->time_to_eat < 0 || vars->time_to_sleep < 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars		vars;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong number of arguments\n", 27);
		return (0);
	}
	if (check_args(ac, av) == 1)
		return (0);
	if (set_variables(ac, av, &vars) == 1)
	{
		write(2, "Wrong argument\n", 16);
		return (0);
	}
	if (set_philos(&vars) == 1)
	{
		write(2, "Initialisation failed\n", 23);
		free_vars(&vars);
		return (0);
	}
	philo(&vars);
	free_vars(&vars);
	return (0);
}
