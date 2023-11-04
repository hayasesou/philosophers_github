

#include "philosopher.h"

void	display_philo_log(t_philo *philo,
		long time_from_start, t_action action)
{

	if (action == GET_FORK)
		printf("%ld %d has taken a fork\n", time_from_start, philo->philo_id);
	else if (action == EAT)
		printf("%ld %d is eating\n", time_from_start, philo->philo_id);
	else if (action == THINK)
		printf("%ld %d is thinking\n", time_from_start, philo->philo_id);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", time_from_start, philo->philo_id);
	else if (action == DIED)
		printf("%s%s%ld %d died%s\n", COLOR_RED, COLOR_BOLD,
			time_from_start, philo->philo_id, COLOR_RESET);
}
