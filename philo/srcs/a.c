/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:42:39 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/29 17:53:08 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_philo_inf(t_inf *inf, t_setting setting, t_share *share)
{
	int i;

	i = -1;
	while(++i < setting.philo_num)
	{
		memset(&inf->philos[i], 0, sizeof(t_philo));
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].num_must_eat = setting.num_must_eat;
		inf->philos[i].left_fork = &inf->forks[i];
		inf->philos[i].right_fork = &inf->forks[(setting.philo_num - 1 + i) % setting.philo_num];
		inf->philos[i].share = share;
		if (i + 1 == 1)
			inf->philos[i].first_philo = true;
		else
			inf->philos[i].first_philo = false;
	}
}

t_return	set_share_info(t_share *share, t_setting setting, t_inf *inf)
{
	int	num_success_init;

	share->philo_num = setting.philo_num;
	share->time2die = setting.time2die;
	share->time2eat = setting.time2eat;
	share->time2sleep = setting.time2sleep;
	share->num_satisfied_philo = 0;
	share->philo_die = false;
	share->share_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * NUM_SHARE_MUTEX);
	if (share->share_mutex == NULL)
	{
		philo_mutex_destroy(inf, share->philo_num, __FILE__, __func__);
		clear_inf_malloc(inf);
		return (print_philo_error("malloc error", MALLOC_ERROR, __FILE__, __func__));
	}
	num_success_init = -1;
	while(++num_success_init< NUM_SHARE_MUTEX)
	{
		if(pthread_mutex_init(&share->share_mutex[num_success_init], NULL) != 0)
			break;
	}
	if(num_success_init != NUM_SHARE_MUTEX)
	{
		philo_mutex_destroy(inf, share->philo_num, __FILE__, __func__);
		clear_inf_malloc(inf);
		philo_share_mutex_destroy(share, num_success_init, __FILE__, __func__);
		print_philo_error("mutex_init error", MUTEX_INIT_ERROR, __FILE__, __func__);
	}
	return (SUCCESS);
}


t_return make_philosopher(t_setting *setting, t_inf *inf)
{
	t_share share;

	if(set_share_info(&share, *setting, inf) != SUCCESS)
		return (ERROR);
	set_philo_inf(inf, *setting, &share);
	t_philo	*philo;
	pthread_mutex_lock(&share.share_mutex[MUTEX_THREAD_START]);
	int i = -1;
	while(++i < setting->philo_num)
	{
		philo = &inf->philos[i];
		if (pthread_create(&(inf->philos_life[i]), NULL, display, philo) != 0)
		{
			philo_join_thread(inf, i - 1, __FILE__, __func__);
			philo_mutex_destroy(inf, setting->philo_num,__FILE__, __func__);
			clear_inf_malloc(inf);
			return (print_philo_error("pthread_create error", PTHREAD_CREATE_ERROR, __FILE__, __func__));
		}
	}
	gettimeofday(&share.start_time, NULL);
	pthread_mutex_unlock(&share.share_mutex[MUTEX_THREAD_START]);

	struct timeval current;
	int k;
	while(1)
	{
		k = -1;
		while (++k < share.philo_num)
		{
			if (inf->philos[k].last_eat.tv_usec == 0)
				continue;
			// pthread_mutex_lock(&philo->share->share_mutex[MUTEX_PRINT]);
			pthread_mutex_lock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
			gettimeofday(&current, NULL);
			if (get_elapsed_time(inf->philos[k].last_eat, current) >= share.time2die)
			{
				pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
				share.philo_die = true;
				display_philo_log(&inf->philos[k], get_time_from_start(share.start_time), DIED);
				pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
				break ;
			}
			pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_LAST_EAT]);
			// pthread_mutex_unlock(&philo->share->share_mutex[MUTEX_PRINT]);
		}
		if (share.philo_die == true)
			break;
	}
	return (SUCCESS);
}

