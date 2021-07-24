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

uint64_t	fire(void)
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((uint64_t)((aux_clock.tv_usec / 1000)) + (aux_clock.tv_sec * 1000));
}

void	*take_fork(void *arg)
{
	t_ph *philo;
	uint64_t aux_time;

	philo = (t_ph *)arg;
	while (1)
	{
	if (philo->ph_n == 1)
	{
		pthread_mutex_lock(philo->rrfork);
		printf("philo %d has taken right fork(%d)", philo->ph_n, philo->rfork);
		pthread_mutex_lock(philo->llfork);
		printf("philo %d has taken left fork(%d) and begin to eat", philo->ph_n, philo->lfork);
		if (philo->last_eat != 0)
		{
			aux_time = fire();
			if ((aux_time - philo->last_eat) > philo->tdie)
			{
				printf("El filosofo %d ha muerto de hambre", philo->ph_n);
				exit(0);
			}

		}
		usleep(philo->teat);
		philo->eat_max++;
		philo->last_eat = fire();
		pthread_mutex_unlock(philo->rrfork);
		printf("philo %d has left right fork(%d)", philo->ph_n, philo->rfork);
		pthread_mutex_unlock(philo->llfork);
		printf("philo %d has left left fork(%d)", philo->ph_n, philo->lfork);
		philo->last_eat = fire();
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		printf("philo %d has taken left fork(%d)", philo->ph_n, philo->rfork);
		pthread_mutex_lock(philo->rrfork);
		printf("philo %d has taken right fork(%d) and begin to eat", philo->ph_n, philo->lfork);
		if (philo->last_eat != 0)
		{
			aux_time = fire();
			if ((aux_time - philo->last_eat) > philo->tdie)
			{
				printf("El filosofo %d ha muerto de hambre", philo->ph_n);
				exit(0);
			}

		}
		usleep(philo->teat);
		philo->eat_max++;
		philo->last_eat = fire();
		pthread_mutex_unlock(philo->llfork);
		printf("philo %d has left left fork(%d)", philo->ph_n, philo->rfork);
		pthread_mutex_unlock(philo->rrfork);
		printf("philo %d has left right fork(%d)", philo->ph_n, philo->lfork);
		philo->last_eat = fire();
	}
	}
	return(NULL);
}

void	create_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_create(&(dat->philos[i].philos), NULL, &take_fork, &dat->philos[i]);
		i++;
	}
}

void	run_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_join((dat->philos[i].philos), NULL);
		i++;
	}
}


uint64_t	fireee()
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((uint64_t)((aux_clock.tv_usec / 1000)) + (aux_clock.tv_sec * 1000));
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
	//run_threads(&dat);
}

