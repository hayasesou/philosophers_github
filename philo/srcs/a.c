/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:42:39 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/07 19:42:06 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	even_philo_number(t_inf *inf, t_setting setting, t_share *share)
{
	int	i;

	i = -1;
	while (++i < setting.philo_num)
	{
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].num_must_eat = setting.num_must_eat;
		inf->philos[i].left_fork = &inf->forks[i];
		inf->philos[i].right_fork
			= &inf->forks[(setting.philo_num - 1 + i) % setting.philo_num];
		inf->philos[i].share = share;
		if (i + 1 == 1)
			inf->philos[i].first_philo = true;
		else
			inf->philos[i].first_philo = false;
		if ((i + 1) % 2 == 1)
			inf->philos[i].usleeptime = 0;
		else if ((i + 1) % 2 == 0)
			inf->philos[i].usleeptime = setting.time2eat / 2;
	}
	// for (int j = 0; j < setting.philo_num; j++)
	//  printf("%ld\n",inf->philos[j].usleeptime);
	// exit (0);
}
static	void setting_start_sleep_time(t_inf *inf, int philo_num, t_setting setting)
{
	int	count_odd_philo;
	int	difference_time;

	count_odd_philo = (philo_num / 2) + 1;
	if (philo_num == 1)
		difference_time = 0;
	else
	difference_time = setting.time2eat / (count_odd_philo - 1);
	int	i;
	int	even;
	int odd;
	int j;

	i = -1;
	odd = 0;
	j = difference_time + setting.time2eat;
	even = 0;
	while (++i < setting.philo_num)
	{
		if ((i + 1) % 2 == 1)
		{
			inf->philos[i].usleeptime = difference_time * odd;
			odd++;
		}
		else if ((i + 1) % 2 == 0)
		{
			inf->philos[i].usleeptime = j + difference_time * even;
			even++;
		}
	}
	//if (philo_num == 3)
	//{
		//inf->philos[0].usleeptime = 0;
		//inf->philos[1].usleeptime = setting.time2eat;
		//inf->philos[2].usleeptime = setting.time2eat / 2;
	//}
	// for(int k = 0 ; k < philo_num; k++)
	//  printf("%ld\n" , inf->philos[k].usleeptime);
	//  exit (0);
}


void	odd_philo_number(t_inf *inf, t_setting setting, t_share *share)
{
	int	i;
	int	even;

	i = -1;
	setting_start_sleep_time(inf, setting.philo_num, setting);
	even = (setting.philo_num / 2) + 1 ;
	while (++i < setting.philo_num)
	{
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].num_must_eat = setting.num_must_eat;
		inf->philos[i].left_fork = &inf->forks[i];
		inf->philos[i].right_fork
			= &inf->forks[(setting.philo_num - 1 + i) % setting.philo_num];
		inf->philos[i].share = share;
		if (i + 1 == 1)
			inf->philos[i].first_philo = true;
		else
			inf->philos[i].first_philo = false;
	}
	setting_start_sleep_time(inf, setting.philo_num, setting);
	// for (int j = 0; j < setting.philo_num; j++)
	//  printf("%ld\n",inf->philos[j].usleeptime);
	// exit (0);
}

void	set_philo_inf(t_inf *inf, t_setting setting, t_share *share)
{
	if (setting.philo_num % 2 == 0)
		even_philo_number(inf, setting, share);
	else if (setting.philo_num % 2 == 1)
		odd_philo_number(inf, setting, share);
}

static void	set_seting2share(t_share *share, t_setting setting)
{
	share->philo_num = setting.philo_num;
	share->time2die = setting.time2die;
	share->time2eat = setting.time2eat;
	share->time2sleep = setting.time2sleep;
	if (setting.philo_num > 150)
		share->sleep_eat_time = LARGER_150;
	else if (setting.philo_num > 80)
		share->sleep_eat_time = LARGER_80;
	else if (setting.philo_num > 30)
		share->sleep_eat_time = LARGER_30;
	else
		share->sleep_eat_time =  LESS_30;
	if (setting.num_must_eat > 0)
		share->num_not_satisfied_philo = setting.philo_num;
	else
		share->num_not_satisfied_philo = NOT_CHECK_NUM_MUST_EAT;
	share->philo_die = false;
}

static void	init_share_mutex(int *num_success_init, t_share *share)
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

	gettimeofday(&share->start_time, NULL);
	while (++i < setting->philo_num)
	{
		philo = &inf->philos[i];
		if (pthread_create(&(inf->philos_life[i]), NULL, philo_life, philo) != 0)
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


