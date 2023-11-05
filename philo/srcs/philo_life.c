/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:20:03 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/05 11:58:51 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait_until_all_thread_maked(t_philo *philo)
{
	struct timeval	current;
	long			time_usleep;

	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_THREAD_START]);
		philo->last_eat = philo->share->start_time;
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_THREAD_START]);
	gettimeofday(&current, NULL);
	time_usleep = get_elapsed_time(philo->share->start_time, current);
	while (time_usleep <= philo->usleeptime)
	{
		gettimeofday(&current, NULL);
		time_usleep = get_elapsed_time(philo->share->start_time, current);
	}
}

void	*philo_life(void *i)
{
	t_philo	*philo;

	philo = (t_philo *)i;
	wait_until_all_thread_maked(philo);
	while (1)
	{
		if (take_fork(philo) == STOP)
			break ;
		if (philo_eat(philo) == STOP)
			break ;
		if (philo_sleep(philo) == STOP)
			break ;
		if (philo_think(philo) == STOP)
			break ;
	}
	return (0);
}
