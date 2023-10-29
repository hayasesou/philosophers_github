/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:13:25 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/29 17:35:41 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_decision	philo_think(t_philo *philo)
{
	long	time_from_start;

	if (check_philo_state(philo, THINK, &time_from_start) == DEAD)
	{
		return (STOP);
	}
	return (CONTINUE);
}
