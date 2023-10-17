/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:33:24 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/17 11:13:56 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void make_philosopher(int *situation);

typedef struct s_philo
{
	
	int philo_id;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int num_must_eat;
	struct timeval	last_eat;
	struct timeval start_time;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	bool *flag;
	bool *die_flag;



	pthread_mutex_t *mutex_print;

}				t_philo;

typedef struct s_inf
{
	pthread_mutex_t *mutexs;
	t_philo	*philos;
	pthread_t *philos_life;
	bool make_all_thread;
	bool	die_flag;
	
	pthread_mutex_t mutex_print;

}			t_inf;

typedef enum e_action
{
	GET_FORK,
	EAT,
	THINK,
	SLEEP,
}			t_action;


typedef	enum e_status
{
	DEAD,
	ALIVE,
}			t_status;



int *set_situation(int ac, char **av);
t_status	take_left_fork(t_philo *philo);
t_status	take_right_fork(t_philo *philo);
t_status	philo_eat(t_philo *philo);
t_status	philo_sleep(t_philo *philo);
t_status	philo_think(t_philo *philo);


#endif
