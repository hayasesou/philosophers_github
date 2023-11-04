/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:09:56 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/04 16:17:27 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_status	take_left_fork(t_philo *philo)
{
	t_status	status;
	long		time_from_start;

	status = check_philo_state(philo, GET_FORK, &time_from_start);
	if (status != HUNGRY)
	{
		if (philo->first_philo == true)
			put_down_fork(philo, RIGHT);
			// pthread_mutex_unlock(philo->right_fork);
		return (status);
	}
	pthread_mutex_lock(philo->left_fork);
	return (status);
}


t_status	take_right_fork(t_philo *philo)
{
	t_status	status;
	long		time_from_start;

	status = check_philo_state(philo, GET_FORK, &time_from_start);
	if (status != HUNGRY)
	{
		if (philo->first_philo == false)
			put_down_fork(philo, LEFT);
			// pthread_mutex_unlock(philo->left_fork);
		return (status);
	}
	pthread_mutex_lock(philo->right_fork);
	return (status);
}


t_decision	take_fork(t_philo *philo)
{
	if (philo->first_philo == true)
	{
		if (take_right_fork(philo) != HUNGRY)
			return (STOP);
		if (take_left_fork(philo) != HUNGRY)
			return (STOP);
	}
	else
	{
		if (take_left_fork(philo) != HUNGRY)
			return (STOP);
		if (take_right_fork(philo) != HUNGRY)
			return (STOP);
	}
	return (CONTINUE);
}
