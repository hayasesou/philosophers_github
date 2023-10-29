/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:34:22 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/28 19:59:31 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main	(int ac, char **av)
{
	t_setting	setting;
	t_inf		inf;

	if (!(ac == 5 || ac == 6))
	{
		printf("Error:\nplease input: ./philo numer_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat\n");
		return (ERROR);
	}
	if (set_situation(av, &setting, &inf) != SUCCESS)
		return (ERROR);
	if(make_philosopher(&setting, &inf) != SUCCESS)
		return (ERROR);
	philo_join_thread(&inf, setting.philo_num, __FILE__, __func__);
	philo_mutex_destroy(&inf, setting.philo_num,__FILE__, __func__);
	clear_inf_malloc(&inf);
	return (0);
}

//__attribute__((destructor))
	//static void destructor(){
		//system("leaks -q philo");
	//}

