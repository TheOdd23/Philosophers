/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 07:01:25 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/17 08:12:08 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (-1);
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	if (nb * neg > INT_MAX || nb * neg < INT_MIN)
		return (-1);
	return (nb * neg);
}

int	ft_is_digit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	else
		return (0);
}

void	begin_time(t_vars *vars)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	vars->beggining_time = ((time.tv_sec * 1000)
		+ (time.tv_usec / 1000));
}

long long	get_time(t_vars *vars)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000)
			+ (time.tv_usec / 1000)) - vars->beggining_time);
}

void	intellisleep(long long timetosleep, t_vars *vars)
{
	long long	start_time;

	start_time = get_time(vars);
	while (get_time(vars) - start_time < timetosleep)
		usleep(100);
}
