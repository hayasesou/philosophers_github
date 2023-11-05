/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:52:05 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/05 11:13:29 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time_from_start(struct timeval start)
{
	long			time_usec;
	long			time_sec;
	long			time_difference;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time_sec = (current.tv_sec - start.tv_sec) * 1000;
	time_usec = (current.tv_usec - start.tv_usec) / 1000;
	time_difference = time_sec + time_usec;
	return (time_difference);
}

long	get_elapsed_time(struct timeval start, struct timeval current)
{
	long			time_usec;
	long			time_sec;
	long			time_difference;

	time_sec = (current.tv_sec - start.tv_sec) * 1000;
	time_usec = (current.tv_usec - start.tv_usec) / 1000;
	time_difference = time_sec + time_usec;
	return (time_difference);
}
