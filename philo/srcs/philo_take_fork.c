/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:09:56 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/02 12:13:00 by hfukushi         ###   ########.fr       */
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
		printf("status == [%d]\n", status);
		// printf("left fork\n");
		if (philo->first_philo == true)
			pthread_mutex_unlock(philo->right_fork);
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
		printf("status == [%d]\n", status);
		// printf("right fork\n");
		if (philo->first_philo == false)
			pthread_mutex_unlock(philo->left_fork);
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
