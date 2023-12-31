/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:33:35 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/05 11:24:59 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	clear_inf_malloc(t_inf *inf)
{
	if (inf->forks != NULL)
	{
		free(inf->forks);
		inf->forks = NULL;
	}
	if (inf->philos != NULL)
	{
		free(inf->philos);
		inf->philos = NULL;
	}
	if (inf->philos_life != NULL)
	{
		free(inf->philos_life);
		inf->philos_life = NULL;
	}
}

void	philo_join_thread(t_inf *inf, int count_created_thread,
			const char *file, const char *func)
{
	int	i;

	i = 0;
	while (i < count_created_thread)
	{
		if (pthread_join(inf->philos_life[i], NULL) != 0)
			print_philo_error("mutex_destroy error",
				PTHREAD_JOIN_ERROR, file, func);
		i++;
	}
}

void	philo_mutex_destroy(t_inf *inf, int count_destroy,
			const char *file, const char *func)
{
	while (count_destroy-- > 0)
	{
		if ((pthread_mutex_destroy(&inf->forks[count_destroy]) != 0))
			print_philo_error("mutex_destroy error",
				MUTEX_DESTROY_ERROR, file, func);
	}
}

void	philo_share_mutex_destroy(t_share *share, int count_destroy,
		const char *file, const char *func)
{
	while (count_destroy > 0)
	{
		if (pthread_mutex_destroy(&share->share_mutex[count_destroy - 1]) != 0)
			print_philo_error("mutex_destroy error",
				MUTEX_DESTROY_ERROR, file, func);
		count_destroy--;
	}
}

void	free_all(t_share *share, t_inf *inf)
{
	clear_inf_malloc(inf);
	free(share->share_mutex);
}
