/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/04 20:00:18 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

void	take_fork(t_ph *philo)
{
	uint64_t timer;
	
	if (philo->ph_n == 1)
	{
		pthread_mutex_lock(philo->rrfork);
		timer = ft_time(0);
		printf("%s|%llu|", CYAN, timer);
		printer(YELLOW, philo->ph_n, philo->rfork, "TOOK right fork");
		pthread_mutex_lock(philo->llfork);
		timer = ft_time(0);
		printf("%s|%llu|", CYAN, timer);
		printer(YELLOW, philo->ph_n,
			philo->lfork, "TOOK left fork and begin to eat");
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		timer = ft_time(0);
		printf("%s|%llu|", CYAN, timer);
		printer(YELLOW, philo->ph_n, philo->lfork, "TOOK left fork");
		pthread_mutex_lock(philo->rrfork);
		timer = ft_time(0);
		printf("%s|%llu|", CYAN, timer);
		printer(YELLOW, philo->ph_n,
			philo->rfork, "TOOK right fork and begin to eat");
	}
}

uint64_t	time_to_eat(t_ph *philo)
{
	uint64_t timer;
		
	ft_usleep(philo->teat);
	philo->eat_max++;
	pthread_mutex_unlock(philo->rrfork);
	timer = ft_time(0);
	printf("%s|%llu|", CYAN, timer);
	printer(GREEN, philo->ph_n, philo->rfork, "PUT DOWN right fork");
	pthread_mutex_unlock(philo->llfork);
	timer = ft_time(0);
	printf("%s|%llu|", CYAN, timer);
	printer(GREEN, philo->ph_n, philo->lfork, "PUT DOWN left fork");
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	uint64_t timer;
	
	timer = ft_time(0);
	printf("%s|%llu|", CYAN, timer);
	printf("%sPhilo [%d] is sleeping zZ zZzZ\n", BLUE, philo->ph_n);
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	uint64_t timer;
	
	timer = ft_time(0);
	printf("%s|%llu|", CYAN, timer);
	printf("%sPhilo [%d] is thinking...\n", MAGENTA, philo->ph_n);
	return (0);
}	

void	*rutine(void *arg)
{
	t_ph		*philo;
	uint64_t	aux_time;
	uint64_t	timer;

	philo = (t_ph *)arg;
	philo->last_eat = ft_time(0);
	while (1)
	{
		take_fork(philo);
		aux_time = ft_time(0);
		printf("filo[%u] va a comer ahora es : %llu, ultima comida: %llu\n",
			philo->ph_n, aux_time, philo->last_eat);
		if ((aux_time - philo->last_eat) > philo->tdie)
		{
			timer = ft_time(0);
			printf("%s|%llu|", CYAN, timer);
			printer(RED, philo->ph_n, 999999999, "is dead");
			exit (0);
		}
		philo->last_eat = ft_time(0);
		time_to_eat(philo);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dat			dat;
	pthread_mutex_t	*mtx;

	if (argc < 5 || argc > 6)
		print_exit("Error\nNumero de argumentos invalido.");
	parsing_argv(argc, argv, &dat);
	mtx = fill_structs(&dat);
	dat.begin = start_clock();
	create_threads(&dat);
	run_threads(&dat);
	turbofree(mtx, &dat);
	return (0);
}
