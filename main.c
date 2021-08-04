/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/20 18:44:20 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "headers/philo.h"

uint64_t	fireee()
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((uint64_t)((aux_clock.tv_usec / 1000)) + (aux_clock.tv_sec * 1000));
}

void	current_time()
{
	long hms;
	struct timeval tv;
	int	sec_per_DHM[3];

	sec_per_DHM[0] = 86400;
	sec_per_DHM[1] = 3600;
	sec_per_DHM[2] = 60;

	gettimeofday(&tv, NULL);
	hms = tv.tv_sec % sec_per_DHM[0];
	hms = (hms + sec_per_DHM[0]) % sec_per_DHM[0];

	printf("Son las: %ld:%02ld:%02ld\n", (hms / sec_per_DHM[1])+2,
	((hms % sec_per_DHM[1]) / sec_per_DHM[2]),
	(hms % sec_per_DHM[1]) % sec_per_DHM[2]);

}

void take_fork(t_ph *philo)
{
	if (philo->ph_n == 1)
	{
		pthread_mutex_lock(philo->rrfork);
		printer(YELLOW, philo->ph_n, philo->rfork, "TOOK left fork");
		pthread_mutex_lock(philo->llfork);
		printer(YELLOW, philo->ph_n, philo->lfork, "TOOK right fork and begin to eat");	
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		printer(YELLOW, philo->ph_n, philo->lfork, "TOOK left fork");
		pthread_mutex_lock(philo->rrfork);
		printer(YELLOW, philo->ph_n, philo->rfork, "TOOK right fork and begin to eat");
	}
}

uint64_t	time_to_eat(t_ph *philo)
{
	struct timeval tv;

	usleep(philo->teat * 100);
	philo->eat_max++;
	pthread_mutex_unlock(philo->rrfork);
	printer(GREEN, philo->ph_n, philo->rfork, "PUT DOWN right fork");
	pthread_mutex_unlock(philo->llfork);
	printer(GREEN, philo->ph_n, philo->lfork, "PUT DOWN left fork");
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	struct timeval tv;

	printf("%sPhilo [%d] is sleeping zZ zZzZ\n", BLUE, philo->ph_n);
	usleep(philo->tsleep * 100);
	printf("%sPhilo [%d] is thinking...\n", CYAN, philo->ph_n);
}	

void	*rutine(void *arg)
{
	t_ph *philo;
	uint64_t aux_time;
	uint64_t aux_time2;
	struct timeval tv;

	philo = (t_ph *)arg;
	philo->last_eat = fireee();
	while(1)
	{
		take_fork(philo);
		aux_time = fireee();
		if ((aux_time - philo->last_eat) > philo->tdie)
		{
			printf("Philo %d is dead.\n", philo->ph_n);
			exit(0);
		}
		philo->last_eat = fireee();
		printf("1:%llu\n", philo->last_eat);
		usleep(10000);
		philo->last_eat = fireee();
		printf("2:%llu\n", philo->last_eat);
		time_to_eat(philo);
		time_to_sleep(philo);
		break;
		
	}
	return(NULL);
}

void	create_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_create(&(dat->philos[i].philos), NULL, rutine, &dat->philos[i]);
		i++;
	}
}

void	run_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_join(dat->philos[i].philos, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_dat dat;

	if (argc < 5 || argc > 6)
		print_exit("Error\nNumero de argumentos invalido.");
	parsing_argv(argc, argv, &dat);
	fill_structs(&dat);
	dat.begin = fireee();
	create_threads(&dat);
	run_threads(&dat);
	free(mtx);
}

