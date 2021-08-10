/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/10 20:13:08 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

uint64_t	time_to_eat(t_ph *philo)
{
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printer(GREEN, philo->ph_n, 999999999, "eats...");
	ft_usleep(philo->teat);
	philo->eat_count++;
	pthread_mutex_unlock(philo->rrfork);
	pthread_mutex_unlock(philo->llfork);
	philo->fork_flags[philo->lfork] = 0;
	philo->fork_flags[philo->rfork] = 0;
	if (philo->eat_count == philo->total_eats)
		(*(philo->flag_eat_max))++;
	if (*(philo->flag_eat_max) == philo->total_ph)
		print_exit("Todos los philos comieron su maximo de comidas.\n");
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	uint64_t	timer;

	timer = ft_time(0);
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printf("%s(%d) is sleeping zZ zZzZ\n", MAGENTA, philo->ph_n);
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printf("%s(%d) is thinking...\n", WHITE, philo->ph_n);
	return (0);
}	

void	*rutine(void *arg)
{
	t_ph		*philo;
	uint64_t	aux_time;

	philo = (t_ph *)arg;
	philo->last_eat = ft_time(0);
	if (philo->ph_n % 2 == 0 || philo->ph_n == philo->total_ph)
		ft_usleep(philo->teat);
	if (philo->ph_n == philo->total_ph)
		ft_usleep(philo->teat);
	while (1)
	{
		take_fork_prior(philo);
		aux_time = ft_time(0);
		dead_check(philo, aux_time);
		philo->caronte_comes = 0;
		philo->last_eat = ft_time(0);
		time_to_eat(philo);
		//max_eats_check(philo);
		time_to_sleep(philo);
		time_to_think(philo);
		caronte_comes(philo);
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
