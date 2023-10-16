

#include "philosopher.h"

display_philo_log(t_philo *philo , t_action action)
{
	if(action == GET_FORK)
	printf("%10ld %4d has taken a left_fork\n", time_from_start, philo->philo_id);
	else if(action == EAT)
	else if(action == THINK)
		printf("%10ld %4d is thinking\n", time_from_start, philo->philo_id);
	else if(action == SLEEP)
		printf("%10ld %4d is sleeping\n", time_from_start, philo->philo_id);
	else if(action ==DIE)
}
