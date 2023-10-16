

#include "philosopher.h"


void take_left_fork(t_philo *philo)
{
	struct timeval current;
	long	time_from_start;

	pthread_mutex_lock(philo->left_fork);
	gettimeofday(&current, NULL);
	current.tv_usec = (current.tv_usec - philo->start_time.tv_usec) / 1000;
	current.tv_sec = (current.tv_sec - philo->start_time.tv_sec) * 1000;
	time_from_start = current.tv_sec + current.tv_usec;

	pthread_mutex_lock(philo->mutex_print);
	if (*(philo->die_flag) == true)
		return ;
	printf("%10ld %4d has taken a left_fork\n", time_from_start, philo->philo_id);
	pthread_mutex_unlock(philo->mutex_print);
}



void take_right_fork(t_philo *philo)
{
	struct timeval current;
	long time_from_start;

	pthread_mutex_lock(philo->right_fork);
	gettimeofday(&current, NULL);
	current.tv_usec = (current.tv_usec - philo->start_time.tv_usec) / 1000;
	current.tv_sec = (current.tv_sec - philo->start_time.tv_sec) * 1000;
	time_from_start = current.tv_sec + current.tv_usec;
	

	pthread_mutex_lock(philo->mutex_print);
	printf("%10ld %4d has taken a right_fork\n", time_from_start, philo->philo_id);
	pthread_mutex_unlock(philo->mutex_print);
}



void	philo_eat(t_philo *philo)
{
	struct timeval current;
	struct timeval eat_start;
	long time_from_eat_start;
	long time_from_start;

	gettimeofday(&current, NULL);
	current.tv_usec = (current.tv_usec - philo->start_time.tv_usec) / 1000;
	current.tv_sec = (current.tv_sec - philo->start_time.tv_sec) * 1000;
	time_from_start = current.tv_sec + current.tv_usec;


	gettimeofday(&(philo->last_eat), NULL);


	pthread_mutex_lock(philo->mutex_print);
	printf("%10ld %4d is eating\n", time_from_start, philo->philo_id);
	pthread_mutex_unlock(philo->mutex_print);

	gettimeofday(&eat_start, NULL);
	time_from_eat_start = 0;
	while(time_from_eat_start <= philo->time2eat)
	{
		gettimeofday(&current, NULL);
		current.tv_usec = (current.tv_usec - eat_start.tv_usec) / 1000;
		current.tv_sec = (current.tv_sec - eat_start.tv_sec) * 1000;
		time_from_eat_start  = current.tv_sec + current.tv_usec;		
	}

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
