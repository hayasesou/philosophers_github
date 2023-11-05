/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:34:49 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/05 11:24:56 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	update_lasteat_and_num_unfulfilled_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
	gettimeofday(&(philo->last_eat), NULL);
	if (philo->num_must_eat > 0)
	{
		philo->num_must_eat--;
		if (philo->num_must_eat == 0)
			philo->share->num_not_satisfied_philo--;
	}
	pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
}

static	void	is_eating(t_philo *philo)
{
	struct timeval	current;
	long			time_from_eat_start;

	gettimeofday(&current, NULL);
	time_from_eat_start = get_elapsed_time(philo->last_eat, current);
	while (time_from_eat_start <= philo->share->time2eat)
	{
		gettimeofday(&current, NULL);
		time_from_eat_start = get_elapsed_time(philo->last_eat, current);
	}
}

t_decision	philo_eat(t_philo *philo)
{
	long		time_from_start;
	t_status	status;

	status = check_philo_state(philo, EAT, &time_from_start);
	if (status != HUNGRY)
	{
		put_down_fork(philo, BOTH);
		return (STOP);
	}
	update_lasteat_and_num_unfulfilled_philo(philo);
	is_eating(philo);
	put_down_fork(philo, BOTH);
	return (CONTINUE);
}
