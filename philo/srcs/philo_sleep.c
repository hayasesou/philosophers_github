
#include "philosopher.h"

static void is_sleeping(t_philo *philo)
{
	struct timeval	current;
	struct timeval	sleep_start;
	long 			time_from_sleep_start;

	gettimeofday(&sleep_start, NULL);
	gettimeofday(&current, NULL);
	time_from_sleep_start = get_elapsed_time(sleep_start, current);
	while(time_from_sleep_start <= philo->share->time2sleep)
	{
		gettimeofday(&current, NULL);
		time_from_sleep_start  = get_elapsed_time(sleep_start, current);
	}
}

t_decision	philo_sleep(t_philo *philo)
{
	long			time_from_start;
	t_status		status;


	status = check_philo_state(philo, SLEEP, &time_from_start);
	if (status != HUNGRY)
		return (STOP);
	is_sleeping(philo);
	return (CONTINUE);
}
