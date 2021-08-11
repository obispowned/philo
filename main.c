/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/11 20:33:18 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

uint64_t	time_to_eat(t_ph *philo)
{
	philo->last_eat = start_clock();
	printer(GREEN, philo->last_eat - philo->start, philo, "eats...");
	ft_usleep(philo->teat);
	philo->eat_count++;
	pthread_mutex_unlock(philo->rrfork);
	pthread_mutex_unlock(philo->llfork);
	philo->fork_flags[philo->lfork] = 0;
	philo->fork_flags[philo->rfork] = 0;
	max_eats_check(philo);
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	uint64_t	timer;

	timer = start_clock();
	printer(MAGENTA, timer - philo->start, philo, "is sleeping zZzZzZ.");
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	uint64_t	timer;

	timer = start_clock();
	printer(WHITE, timer - philo->start, philo, "is thinking...");
	return (0);
}	

void	*rutine(void *arg)
{
	t_ph		*philo;

	philo = (t_ph *)arg;
	philo->last_eat = start_clock();
	if (philo->ph_n % 2 == 0 || (philo->ph_n == philo->total_ph && philo->total_ph % 2 != 0))
		ft_usleep(philo->teat);
	/*if ((philo->ph_n == philo->total_ph) && (philo->total_ph % 2 != 0))
		ft_usleep(philo->teat);*/
	while (1)
	{
		take_fork_prior(philo);
		dead_check(philo);
		philo->caronte_comes = 0;
		time_to_eat(philo);
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
	dat.begin = start_clock();
	mtx = fill_structs(&dat);
	create_threads(&dat);
	run_threads(&dat);
	turbofree(mtx, &dat);
	return (0);
}
