/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:58:43 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/29 16:14:19 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_status	check_philo_state(t_philo *philo, t_action action, long *time_from_start)
{
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_PRINT]);
	if (philo->share->philo_die == true)
	{
		pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
		return (DEAD);
	}
	*time_from_start = get_time_from_start(philo->share->start_time);
	display_philo_log(philo, *time_from_start, action);
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
	return (HUNGRY);
}
