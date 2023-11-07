/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:58:43 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/07 19:04:44 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_status	check_philo_state(t_philo *philo, t_action action,
				long *time_from_start)
{
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_PRINT]);
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
	if (philo->share->num_not_satisfied_philo == 0)
	{
		pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
		pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
		return (ALL_SATISFIED);
	}
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_DIE]);
	if (philo->share->philo_die == true)
	{
		pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_DIE]);
		pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_DIE]);
	*time_from_start = get_time_from_start(philo->share->start_time);
	display_philo_log(philo, *time_from_start, action);
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
	return (HUNGRY);
}

void	put_down_fork(t_philo *philo, t_fork fork)
{
	if (fork == BOTH)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else if (fork == RIGHT)
		pthread_mutex_unlock(philo->right_fork);
	else if (fork == LEFT)
		pthread_mutex_unlock(philo->left_fork);
}
