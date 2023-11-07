/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:33:24 by hfukushi          #+#    #+#             */
/*   Updated: 2023/11/07 18:47:35 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# define NO_ARG	INT_MIN;
# define NOT_CHECK_NUM_MUST_EAT -1;

# define COLOR_RED	"\e[31m"
# define COLOR_RESET	"\e[0m"
# define COLOR_BOLD	"\e[1m"

# define LARGER_150 2000
# define LARGER_80 1000
# define LARGER_30 500
# define LESS_30 100

# define X_USLEEP 1000

# define A "Error:please input"
# define C ": ./philo numer_of_philosophers time_to_die "
# define IS "time_to_eat time_to_sleep number_of_"
# define INVALID "times_each_philosopher_must_eat\n"


typedef enum e_return
{
	SUCCESS,
	ERROR,
	MALLOC_ERROR,
	MUTEX_INIT_ERROR,
	MUTEX_DESTROY_ERROR,
	PTHREAD_CREATE_ERROR,
	PTHREAD_JOIN_ERROR,
	INVALID_ARG,
	VALID_ARG,
}		t_return;

//philosopher action
typedef enum e_action
{
	GET_FORK,
	EAT,
	THINK,
	SLEEP,
	DIED,
}			t_action;

typedef enum e_decision
{
	CONTINUE,
	STOP,
}		t_decision;

// status of philo
typedef enum e_status
{
	DEAD,
	HUNGRY,
	ALL_SATISFIED,
}			t_status;

typedef enum e_fork
{
	LEFT,
	RIGHT,
	BOTH,
}	t_fork;

typedef struct setting
{
	int	philo_num;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	num_must_eat;
}		t_setting;

# define NUM_SHARE_MUTEX 4

typedef enum e_share_mutex
{
	MUTEX_THREAD_START,
	MUTEX_DIE,
	MUTEX_LAST_EAT,
	MUTEX_PRINT,
}		t_share_mutex;

typedef struct s_share
{
	int				philo_num;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num_not_satisfied_philo;
	bool			philo_die;
	int				sleep_eat_time;
	struct timeval	start_time;
	pthread_mutex_t	*share_mutex;
}			t_share;

typedef struct s_philo
{
	int				philo_id;
	int				num_must_eat;
	struct timeval	last_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			usleeptime;
	bool			first_philo;
	t_share			*share;
}				t_philo;

typedef struct s_inf
{
	pthread_mutex_t	*forks;
	pthread_t		*philos_life;
	t_philo			*philos;
}			t_inf;

//time_statmp.c
long		get_time_from_start(struct timeval start);
long		get_elapsed_time(struct timeval start, struct timeval current);

//check philo and display log
t_status	check_philo_state(t_philo *philo, t_action action, long *time_from_start);
void		display_philo_log(t_philo *philo, long time_from_start, t_action action);
void		observe_philo_state(t_share *share, t_inf *inf);
void	x_usleep(int sleep_time);

//philosopher_action
void		*philo_life(void *i);
void		wait_until_all_thread_maked(t_philo *philo);
t_decision	philo_eat(t_philo *philo);
t_decision	philo_sleep(t_philo *philo);
t_decision	philo_think(t_philo *philo);

//take_fork.c
t_decision	take_fork(t_philo *philo);
t_status	take_left_fork(t_philo *philo);
t_status	take_right_fork(t_philo *philo);
void		put_down_fork(t_philo *philo, t_fork fork);

//setting infomation
void		set_philo_inf(t_inf *inf, t_setting setting, t_share *share);
t_return	set_situation(char **av, t_setting *setting, t_inf *inf);

//thread create
t_return	make_philosopher(t_setting *setting, t_inf *inf, t_share *share);

//error_handling
t_return	print_philo_error(char *serror_masseage, t_return return_val, const char *file, const char *func);
t_return	print_invalid_arg(t_return return_val, char * error_arg_message);

//clear mutex & malloc
void		clear_inf_malloc(t_inf *inf);
void		free_all(t_share *share, t_inf *inf);
void		philo_mutex_destroy(t_inf *inf, int count_destroy, const char *file, const char *func);
void		philo_share_mutex_destroy(t_share *share, int count_destroy, const char * file, const char *func);
void		philo_join_thread(t_inf *inf, int count_created_thread, const char *file, const char *func);

#endif
