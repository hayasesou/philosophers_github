

#include "philosopher.h"

static long handle_overflow(long num, int digit);

int ft_philo_atoi(char *str)
{
	long num;

	num = 0;
	if (*str == '+')
		str++;
	if (*str > '9' || *str < '0')
		return (-1);
	while ('0' <= *str && *str <= '9')
	{
		if (handle_overflow(num, *str - '0') == 1)
			return (-1);
		num = num * 10 + (*str - '0');
		str++;
	}
	if (*str !=  '\0')
		return (-1);
	return  ((int)num);
}

static long handle_overflow(long num, int digit)
{
	if(num > INT_MAX / 10 ||(num == INT_MAX / 10 && digit % 10 > INT_MAX % 10))
		return (1);
	return (0);
}


int check_argument(int ac, int *situation)
{
	int	isinvalid;

	isinvalid = 0;
	if (situation[0] == 0 || situation[0] == -1)
		isinvalid = 1;
	if (situation[1] == 0 || situation[1] == -1)
		isinvalid = 1;
	if (situation[2] == 0 || situation[2] == -1)
		isinvalid = 1;
	if (situation[3] == 0 || situation[3] == -1)
		isinvalid = 1;
	if (ac == 6 &&  situation[4] == -1)
		isinvalid = 1;
	return  (isinvalid);
}


int *set_situation(int ac,char **av)
{
	int *situation;
	int i;

	situation = (int *)malloc(sizeof(int) * (ac - 1));
	i = 0;
	while(i < ac -1)
	{
		situation[i] = ft_philo_atoi(av[i + 1]);
		i++;
	}
	if (check_argument(ac, situation) == 1)
	{
		free (situation);
		printf("Error : wrong argument\n");
		return (NULL);
	}
	return (situation);
}
