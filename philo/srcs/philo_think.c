/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:13:25 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/04 14:11:11 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_decision	philo_think(t_philo *philo)
{
	long	time_from_start;
	t_status status;

	status = check_philo_state(philo, THINK, &time_from_start);
	if (status != HUNGRY)
		return (STOP);
	return (CONTINUE);
}
