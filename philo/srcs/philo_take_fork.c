/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:09:56 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/29 18:05:23 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_status	take_left_fork(t_philo *philo)
{
	t_status status;
	long	time_from_start;

	pthread_mutex_lock(philo->left_fork);
	status = check_philo_state(philo, GET_FORK, &time_from_start);
	if (status == DEAD)
	{
		// printf("left fork\n");
		if (philo->first_philo == true)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
		}
	}
	return(status);
}


t_status	take_right_fork(t_philo *philo)
{
	t_status status;
	long time_from_start;

	pthread_mutex_lock(philo->right_fork);
	status = check_philo_state(philo, GET_FORK, &time_from_start);
	if (status == DEAD)
	{
		// printf("right fork\n");
		if (philo->first_philo == true)
			pthread_mutex_unlock(philo->right_fork);
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
	}
	return (status);
}


t_decision	take_fork(t_philo *philo)
{
	if (philo->first_philo == true)
	{
		if (take_right_fork(philo) == DEAD)
			return (STOP);
		if (take_left_fork(philo) == DEAD)
			return (STOP);
	}
	else
	{
		if (take_left_fork(philo) == DEAD)
			return (STOP);
		if (take_right_fork(philo) == DEAD)
			return (STOP);
	}
	return	(CONTINUE);
}
