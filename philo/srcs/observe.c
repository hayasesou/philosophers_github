/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:29:37 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/06 12:28:57 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static	bool	check_one_philo_die(t_inf *inf, t_share *share,
		long time_from_last_eat, int philo_id)
{
	if (time_from_last_eat >= share->time2die)
	{
		pthread_mutex_lock(&share->share_mutex[MUTEX_DIE]);
		share->philo_die = true;
		pthread_mutex_unlock(&share->share_mutex[MUTEX_DIE]);
		display_philo_log(&inf->philos[philo_id],
			get_time_from_start(share->start_time), DIED);
		printf("time last_eat == %ld\n", time_from_last_eat);
		pthread_mutex_unlock(&share->share_mutex[MUTEX_PRINT]);
		return (true);
	}
	return (false);
}

static	bool	check_all_philo_satisified(t_share *share)
{
	pthread_mutex_lock(&share->share_mutex[MUTEX_LAST_EAT]);
	if (share->num_not_satisfied_philo == 0)
	{
		pthread_mutex_unlock(&share->share_mutex[MUTEX_LAST_EAT]);
		pthread_mutex_unlock(&share->share_mutex[MUTEX_PRINT]);
		return (true);
	}
	return (false);
}

void	observe_philo_state(t_share *share, t_inf *inf)
{
	struct timeval	current;
	long			time_from_last_eat;
	int				i;

	while (1)
	{
		i = -1;
		while (++i < share->philo_num)
		{
			if (inf->philos[i].last_eat.tv_usec == 0)
				continue ;
			pthread_mutex_lock(&share->share_mutex[MUTEX_PRINT]);
			if (check_all_philo_satisified(share) == true)
				return ;
			gettimeofday(&current, NULL);
			time_from_last_eat
				= get_elapsed_time(inf->philos[i].last_eat, current);
			pthread_mutex_unlock(&share->share_mutex[MUTEX_LAST_EAT]);
			if (check_one_philo_die(inf, share, time_from_last_eat, i) == true)
				return ;
			pthread_mutex_unlock(&share->share_mutex[MUTEX_PRINT]);
		}
		usleep(100);
	}
}
