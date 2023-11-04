/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:34:02 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/04 18:39:05 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// static long	handle_overflow(long num, int digit);

int	ft_philo_atoi(char *str)
{
	long	num;

	num = 0;
	if (*str == '+')
		str++;
	if (*str > '9' || *str < '0')
		return (-1);
	while ('0' <= *str && *str <= '9')
	{
		if (num > INT_MAX / 10
			|| (num == INT_MAX / 10 && (*str - '0') % 10 > INT_MAX % 10))
			return (-1);
		num = num * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)num);
}

t_return	check_argument(t_setting *setting)
{

	if (setting->philo_num == 0 || setting->philo_num == -1)
		return (print_invalid_arg(INVALID_ARG, "number_of_philosopher"));
	if (setting->time2die == 0 || setting->time2die == -1)
		return (print_invalid_arg(INVALID_ARG, "time_to_die"));
	if (setting->time2eat == 0 || setting->time2eat == -1)
		return (print_invalid_arg(INVALID_ARG, "time_to_eat"));
	if (setting->time2sleep == 0 || setting->time2sleep == -1)
		return (print_invalid_arg(INVALID_ARG, "time_to_sleep"));
	if (setting->num_must_eat == 0 || setting->num_must_eat == -1)
		return (print_invalid_arg(INVALID_ARG,
				"number_of_times_each_philosopher_must_eat"));

	return (VALID_ARG);
}

t_return	init_mutex_of_t_inf(t_inf *inf, t_setting setting)
{
	int	count_success_mutex_init;

	count_success_mutex_init = -1;
	while (++count_success_mutex_init < setting.philo_num)
	{
		if (pthread_mutex_init(
				&inf->forks[count_success_mutex_init], NULL) != 0)
		{
			print_philo_error("mutex_init error",
				MUTEX_INIT_ERROR, __FILE__, __func__);
			break ;
		}
	}
	if (count_success_mutex_init < setting.philo_num)
	{
		philo_mutex_destroy(inf, count_success_mutex_init, __FILE__, __func__);
		clear_inf_malloc(inf);
		return (MUTEX_INIT_ERROR);
	}
	return (SUCCESS);
}

static	t_return	preapration_t_inf(t_inf *inf, t_setting *setting)
{
	memset(inf, 0, sizeof(t_inf));
	inf->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * setting->philo_num);
	if (inf->forks == NULL)
		return (print_philo_error("malloc error",
				MALLOC_ERROR, __FILE__, __func__));
	inf->philos = (t_philo *)malloc(sizeof(t_philo) * setting->philo_num);
	if (inf->philos == NULL)
	{
		clear_inf_malloc(inf);
		return (print_philo_error("malloc error",
				MALLOC_ERROR, __FILE__, __func__));
	}
	inf->philos_life = (pthread_t *)malloc(
			sizeof(pthread_t) * setting->philo_num);
	if (inf->philos_life == NULL)
	{
		clear_inf_malloc(inf);
		return (print_philo_error("malloc error",
				MALLOC_ERROR, __FILE__, __func__));
	}
	return (init_mutex_of_t_inf(inf, *setting));
}


t_return	set_situation(char **av, t_setting *setting, t_inf *inf)
{
	setting->philo_num = ft_philo_atoi(av[1]);
	setting->time2die = ft_philo_atoi(av[2]);
	setting->time2eat = ft_philo_atoi(av[3]);
	setting->time2sleep = ft_philo_atoi(av[4]);
	if (av [5])
		setting->num_must_eat = ft_philo_atoi(av[5]);
	else
		setting->num_must_eat = NO_ARG;
	if (check_argument(setting) == INVALID_ARG)
		return (ERROR);
	if (preapration_t_inf(inf, setting) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
