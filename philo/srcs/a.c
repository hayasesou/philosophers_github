
#include "philosopher.h"


void	wait_until_all_thread_maked(t_philo *philo)
{
	while(philo->flag == false)
		;
	if (philo->start_time.tv_usec == 0)
		gettimeofday(&(philo->start_time), NULL);
	gettimeofday(&(philo->last_eat), NULL);
}


void *display(void *i)
{
	t_philo *philo;

	philo = (t_philo *)i;
	wait_until_all_thread_maked(philo);
	while(1)
	{
		take_left_fork(philo);
		take_right_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}

	return (0);
}


void	set_philo_inf(t_inf *inf, int *situation)
{
	int i;

	i = -1;
	while(++ i < situation[0])
	{
		inf->philos[i].philo_id = i + 1;
		inf->philos[i].time2die = situation[1];
		inf->philos[i].time2eat = situation[2];
		inf->philos[i].time2sleep = situation[3];
		inf->philos[i].left_fork = &inf->mutexs[i];
		inf->philos[i].right_fork = &inf->mutexs[(situation[0] - 1 + i) % situation[0]];
		inf->philos[i].flag = &inf->make_all_thread;
		inf->philos[i].die_flag = &(inf->die_flag);
		inf->philos[i].mutex_print = &(inf->mutex_print);
	}
	free(situation);
}


void make_philosopher(int *situation)
{
	t_inf inf;

	inf.philos_life = (pthread_t *)malloc(sizeof(pthread_t) * situation[0]);
	inf.philos = (t_philo *)malloc(sizeof(t_philo) * situation[0]);
	inf.mutexs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * situation[0]);
	inf.die_flag = false;



	pthread_mutex_init(&inf.mutex_print, NULL);



	int i = -1;
	while (++i < situation[0])
		pthread_mutex_init(&inf.mutexs[i], NULL);
	set_philo_inf(&inf, situation);

	i = -1;
	t_philo	*philo;

	while(++i < situation[0])
	{
		philo = &inf.philos[i];
	 	pthread_create(inf.philos_life, NULL, display, philo);
	}
	inf.make_all_thread = true;
	

	int k;
	struct timeval now;
	struct timeval tmp_now;
	long time_from_last_eat;
	while(1)
	{
		k = -1;
		while(++k < situation[0])
		{
			gettimeofday(&now, NULL);
			tmp_now = now;
			//printf("check1 %d %d\n", tmp_now.tv_usec,  inf.philos[k].last_eat.tv_usec);
			//int x = inf.philos[k].last_eat.tv_sec;
			//int y = inf.philos[k].last_eat.tv_usec;
			while(inf.philos[k].last_eat.tv_sec == 0)
				;
			now.tv_sec = (now.tv_sec - inf.philos[k].last_eat.tv_sec) * 1000;
			now.tv_usec = (now.tv_usec - inf.philos[k].last_eat.tv_usec) / 1000;
			time_from_last_eat = now.tv_sec + now.tv_usec;
			if (time_from_last_eat >= situation[1] && inf.philos[k].last_eat.tv_sec != 0)
			{
				inf.die_flag = true;
				tmp_now.tv_sec = (tmp_now.tv_sec - inf.philos[k].start_time.tv_sec) * 1000;
				tmp_now.tv_usec = (tmp_now.tv_usec - inf.philos[k].start_time.tv_usec) / 1000;
				pthread_mutex_lock(&(inf.mutex_print));
				printf("\e[31m");
				printf("%10ld %4d died\n", (long)(tmp_now.tv_sec + tmp_now.tv_usec), inf.philos[k].philo_id);
				printf("\e[0m");


				printf("philo %d: time_from_last =  %ld\n", inf.philos[k].philo_id, time_from_last_eat);
				//printf("putain %ld: %d\n", tmp_now.tv_sec, tmp_now.tv_usec);
				//printf("putain %ld: %d\n", now.tv_sec, now.tv_usec);
				//printf("putain %ld: %d\n", inf.philos[k].last_eat.tv_sec, inf.philos[k].last_eat.tv_usec);
				//printf("-----------putain %d: %d------------\n",  x, y);
				exit(0);
			}
		}
	}

	while(i-- > 0)
	{
		pthread_join(*inf.philos_life, NULL);
		inf.philos_life--;
	}
	while (++i < situation[0])
		pthread_mutex_destroy(&inf.mutexs[i]);
}

