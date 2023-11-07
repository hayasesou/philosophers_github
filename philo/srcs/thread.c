/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:47:14 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/07 20:22:18 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	even_philo_number(t_inf *inf, t_setting setting, t_share *share)
{
	int	i;

	i = -1;
	while (++i < setting.philo_num)
	{
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].num_must_eat = setting.num_must_eat;
		inf->philos[i].left_fork = &inf->forks[i];
		inf->philos[i].right_fork
			= &inf->forks[(setting.philo_num - 1 + i) % setting.philo_num];
		inf->philos[i].share = share;
		if (i + 1 == 1)
			inf->philos[i].first_philo = true;
		else
			inf->philos[i].first_philo = false;
		if ((i + 1) % 2 == 1)
			inf->philos[i].usleeptime = 0;
		else if ((i + 1) % 2 == 0)
			inf->philos[i].usleeptime = setting.time2eat / 2;
	}
}

static	void	setting_start_sleep_time(t_inf *inf,
	t_setting setting, int even, int odd)
{
	const int	count_odd_philo = (setting.philo_num / 2) + 1;
	int			difference_time;
	int			i;
	int			even_start;

	if (setting.philo_num == 1)
		difference_time = 0;
	else
	difference_time = setting.time2eat / (count_odd_philo - 1);
	i = -1;
	even_start = difference_time + setting.time2eat;
	while (++i < setting.philo_num)
	{
		if ((i + 1) % 2 == 1)
		{
			inf->philos[i].usleeptime = difference_time * odd;
			odd++;
		}
		else if ((i + 1) % 2 == 0)
		{
			inf->philos[i].usleeptime = even_start + difference_time * even;
			even++;
		}
	}
}

void	odd_philo_number(t_inf *inf, t_setting setting, t_share *share)
{
	int	i;

	i = -1;
	while (++i < setting.philo_num)
	{
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].num_must_eat = setting.num_must_eat;
		inf->philos[i].left_fork = &inf->forks[i];
		inf->philos[i].right_fork
			= &inf->forks[(setting.philo_num - 1 + i) % setting.philo_num];
		inf->philos[i].share = share;
		if (i + 1 == 1)
			inf->philos[i].first_philo = true;
		else
			inf->philos[i].first_philo = false;
	}
	setting_start_sleep_time(inf, setting, 0, 0);
}
