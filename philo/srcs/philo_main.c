/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:34:22 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/13 01:45:17 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"
  
int main (int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
	 {      
		 printf("Error:\nplease input: ./philo numer_of_phi    losophers time_to_die time_to_eat time_to_sleep number_of_    times_each_philosopher_must_eat\n");
		 return (1);
	 }
	int *situation = set_situation(ac, av);
	if (situation == NULL)
		return (-1);
	//for (int k = 0; k < ac - 1; k++)
	//{
	//	printf("situation[%d] = %d\n",k, situation[k]);
	//}
	make_philosopher(situation);
	return(0);
 }

__attribute__((destructor))
	static void destructor(){
		system("leaks -q philo");
	}

