/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/05 20:50:57 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

void	take_fork(t_ph *philo)
{	
	if (philo->ph_n == 1)
	{
		pthread_mutex_lock(philo->rrfork);
		printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n, philo->rfork, "has taken right fork");
		pthread_mutex_lock(philo->llfork);
		printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n,
			philo->lfork, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n, philo->lfork, "has taken left fork");
		pthread_mutex_lock(philo->rrfork);
		printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n,
			philo->rfork, "has taken right fork");
	}
}

uint64_t	time_to_eat(t_ph *philo)
{
	printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
	printer(GREEN, philo->ph_n, 999999999, "eats...");
	ft_usleep(philo->teat);
	philo->eat_max++;
	pthread_mutex_unlock(philo->rrfork);
	pthread_mutex_unlock(philo->llfork);
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	uint64_t timer;
	
	timer = ft_time(0);
	printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
	printf("%s(%d) is sleeping zZ zZzZ\n", MAGENTA, philo->ph_n);
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	printf("%s|%llu ms| ", CYAN, ft_time(0) - philo->start);
	printf("%s(%d) is thinking...\n", WHITE, philo->ph_n);
	//ft_usleep(1);
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
		if (philo->caronte_comes == 1)
			take_fork(philo);
		else
		{
			ft_usleep(1);
			take_fork(philo);
		}
		aux_time = ft_time(0);
		if ((aux_time - philo->last_eat) > philo->tdie)
		{
			timer = ft_time(0);
			printf("%s|%llu ms| ", CYAN, timer - philo->start);
			printer(RED, philo->ph_n, 999999999, "is dead");
			exit (0);
		}
		philo->last_eat = ft_time(0);
		philo->caronte_comes = 0;
		time_to_eat(philo);
		time_to_sleep(philo);
		time_to_think(philo);
		if ((ft_time(0) - philo->last_eat) >= philo->tdie / 2)
		{
			philo->caronte_comes = 1;
			printer(RED, philo->ph_n, 999999999, "Caronte en su canoa esta en camino a por tu alma");
		}
		else
			ft_usleep(1);
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
