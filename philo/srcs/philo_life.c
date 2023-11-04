/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:20:03 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/04 18:46:30 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait_until_all_thread_maked(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_THREAD_START]);
		philo->last_eat = philo->share->start_time;
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_THREAD_START]);
}


void	*display(void *i)
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
