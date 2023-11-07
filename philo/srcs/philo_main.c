/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:34:22 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/07 18:48:45 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main	(int ac, char **av)
{
	t_setting	setting;
	t_inf		inf;
	t_share		share;

	if (!(ac == 5 || ac == 6))
	{
		printf("%s%s%s%s%s%s", COLOR_RED, COLOR_BOLD, A, C, IS, INVALID);
		return (ERROR);
	}
	if (set_situation(av, &setting, &inf) != SUCCESS)
		return (ERROR);
	if (make_philosopher(&setting, &inf, &share) != SUCCESS)
		return (ERROR);
	philo_join_thread(&inf, setting.philo_num, __FILE__, __func__);
	philo_share_mutex_destroy(&share, NUM_SHARE_MUTEX, __FILE__, __func__);
	philo_mutex_destroy(&inf, setting.philo_num, __FILE__, __func__);
	free_all(&share, &inf);
	return (0);
}

//__attribute__((destructor))
	//static void destructor(){
		//system("leaks -q philo");
	//}
