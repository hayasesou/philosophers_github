
#include "philosopher.h"


t_status philo_sleep(t_philo *philo)
{
	struct	timeval current;
	struct	timeval sleep_start;
	long	time_from_sleep_start;
	long	time_from_start;

	gettimeofday(&current, NULL);
	current.tv_usec = (current.tv_usec - philo->start_time.tv_usec) / 1000;
	current.tv_sec = (current.tv_sec - philo->start_time.tv_sec) * 1000;
	time_from_start = current.tv_sec + current.tv_usec;
	

	pthread_mutex_lock(philo->mutex_print);
	
	if (*(philo->die_flag) == true)
	{
		pthread_mutex_unlock(philo->mutex_print);
		return (DEAD);
	}
	printf("%10ld %4d is sleeping\n", time_from_start, philo->philo_id);
	pthread_mutex_unlock(philo->mutex_print);

	gettimeofday(&sleep_start, NULL);
	time_from_sleep_start = 0;
	while(time_from_sleep_start <= philo->time2sleep)
	{
		gettimeofday(&current, NULL);
		current.tv_usec = (current.tv_usec - sleep_start.tv_usec) / 1000;
		current.tv_sec = (current.tv_sec - sleep_start.tv_sec) * 1000;
		time_from_sleep_start  = current.tv_sec + current.tv_usec;		
	}
	return (ALIVE);
}
