/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:34:49 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/29 18:05:34 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


t_decision	philo_eat(t_philo *philo)
{
	struct timeval current;
	long time_from_eat_start;
	long time_from_start;

	if (check_philo_state(philo, EAT, &time_from_start) == DEAD)
	{
		// printf("eat\n");
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (STOP);
	}
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
	gettimeofday(&(philo->last_eat), NULL);
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
	gettimeofday(&current, NULL);
	time_from_eat_start = get_elapsed_time(philo->last_eat, current);
	while(time_from_eat_start <= philo->share->time2eat)
	{
		gettimeofday(&current, NULL);
		time_from_eat_start  = get_elapsed_time(philo->last_eat, current);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (CONTINUE);
}
