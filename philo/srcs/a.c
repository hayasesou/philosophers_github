/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:42:39 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/04 18:22:34 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_philo_inf(t_inf *inf, t_setting setting, t_share *share)
{
	int	i;

	i = -1;
	while (++i < setting.philo_num)
	{
		memset(&inf->philos[i], 0, sizeof(t_philo));
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].num_must_eat = setting.num_must_eat;
		inf->philos[i].left_fork = &inf->forks[i];
		inf->philos[i].right_fork =&inf->forks[(setting.philo_num - 1 + i) % setting.philo_num];
		inf->philos[i].share = share;
		if (i + 1 == 1)
			inf->philos[i].first_philo = true;
		else
			inf->philos[i].first_philo = false;
	}
}

static void	set_seting2share(t_share *share, t_setting setting)
{
	share->philo_num = setting.philo_num;
	share->time2die = setting.time2die;
	share->time2eat = setting.time2eat;
	share->time2sleep = setting.time2sleep;
	if (setting.num_must_eat > 0)
		share->num_not_satisfied_philo = setting.philo_num;
	else
		share->num_not_satisfied_philo = NOT_CHECK_NUM_MUST_EAT;
	share->philo_die = false;
}

static void init_share_mutex(int *num_success_init, t_share *share)
{
	*num_success_init = -1;
	while (++(*num_success_init) < NUM_SHARE_MUTEX)
	{
		if (pthread_mutex_init(&share->share_mutex[*num_success_init], NULL)
			!= 0)
			break ;
	}
}


t_return	set_share_info(t_share *share, t_setting setting, t_inf *inf)
{
	int	num_success_init;

	set_seting2share(share, setting);
	share->share_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* NUM_SHARE_MUTEX);
	if (share->share_mutex == NULL)
	{
		philo_mutex_destroy(inf, share->philo_num, __FILE__, __func__);
		clear_inf_malloc(inf);
		return (print_philo_error("malloc error",
				MALLOC_ERROR, __FILE__, __func__));
	}
	//num_success_init = -1;
	//while (++num_success_init < NUM_SHARE_MUTEX)
	//{
		//if (pthread_mutex_init(&share->share_mutex[num_success_init], NULL)
			//!= 0)
			//break ;
	//}
	init_share_mutex(&num_success_init, share);
	if (num_success_init != NUM_SHARE_MUTEX)
	{
		philo_share_mutex_destroy(share, num_success_init, __FILE__, __func__);
		philo_mutex_destroy(inf, share->philo_num, __FILE__, __func__);
		free_all(share, inf);
		print_philo_error("mutex_init error",
			MUTEX_INIT_ERROR, __FILE__, __func__);
	}
	return (SUCCESS);
}


t_return	make_philosopher(t_setting *setting, t_inf *inf, t_share *share)
{
	t_philo	*philo;
	int		i;

	if (set_share_info(share, *setting, inf) != SUCCESS)
		return (ERROR);
	set_philo_inf(inf, *setting, share);
	pthread_mutex_lock(&share->share_mutex[MUTEX_THREAD_START]);
	i = -1;
	while (++i < setting->philo_num)
	{
		philo = &inf->philos[i];
		if (pthread_create(&(inf->philos_life[i]), NULL, display, philo) != 0)
		{
			philo_join_thread(inf, i - 1, __FILE__, __func__);
			philo_mutex_destroy(inf, setting->philo_num, __FILE__, __func__);
			clear_inf_malloc(inf);
			return (print_philo_error("pthread_create error",
					PTHREAD_CREATE_ERROR, __FILE__, __func__));
		}
	}
	gettimeofday(&share->start_time, NULL);
	pthread_mutex_unlock(&share->share_mutex[MUTEX_THREAD_START]);

	observe_philo_state(share, inf);
	return (SUCCESS);
}


