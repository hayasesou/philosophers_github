
#include "philosopher.h"



void	philo_think(t_philo *philo)
{
	struct timeval current;
	long	time_from_start;

	gettimeofday(&current, NULL);
	current.tv_usec = (current.tv_usec - philo->start_time.tv_usec) / 1000;
	current.tv_sec = (current.tv_sec - philo->start_time.tv_sec) * 1000;
	time_from_start = current.tv_sec + current.tv_usec;


	pthread_mutex_lock(philo->mutex_print);
	printf("%10ld %4d is thinking\n", time_from_start, philo->philo_id);
	pthread_mutex_unlock(philo->mutex_print);
}
