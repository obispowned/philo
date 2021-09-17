/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/09/17 19:56:31 by agutierr         ###   ########.fr       */
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
	uint64_t	timer;
	
	philo = (t_ph *)arg;
	timer = start_clock();
	if ((philo->ph_n % 2 == 0 || (philo->ph_n == philo->total_ph && philo->total_ph % 2 != 0)) && philo->total_ph != 1)
		ft_usleep(philo->teat);
	if (((philo->ph_n == philo->total_ph) && (philo->total_ph % 2 != 0)) && philo->total_ph != 1)
		ft_usleep(philo->teat);
	while (1)
	{
		take_fork_prior(philo);
		//philo->caronte_comes = 0;
		time_to_eat(philo);
		time_to_sleep(philo);
		time_to_think(philo);
		//caronte_comes(philo);
		if (philo->eat_count == philo->total_eats)
			(*(philo->full_eats))+=1;
	}
	return (NULL);
}

void	printerd(char *color, uint64_t timer, t_ph *philo, char *msg)
{
	pthread_mutex_lock(philo->mprint);
	printf("%s| %-8llu ms | %s(%d) %s.\n", CYAN, timer, color, philo->ph_n, msg);
}

int strafing_killer(t_dat *dat, int i)
{
	uint64_t	timer;

	timer = start_clock();
	printer(RED, timer - dat->begin, &(dat->philos[i]), "is dead");
	return (0);
}

int	dead_checker(t_dat *dat)
{
	int	i;
	uint64_t		timer;

	i = 0;
	while (1)
	{
		timer = start_clock();
		if ((timer - dat->philos[i].last_eat) > dat->tdie)
			return (strafing_killer(dat, i));
		if (*dat->philos[0].full_eats == dat->total_eats)
			return(1);
		i++;
		if (i == dat->total_ph)
			i = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_dat			dat;

	if (argc < 5 || argc > 6)
		print_exit("Error\nNumero de argumentos invalido.");
	parsing_argv(argc, argv, &dat);
	fill_structs(&dat);
	create_threads(&dat);
	return(dead_checker(&dat));
	//run_threads(&dat);
	//turbofree(mtx, &dat);
	return (0);
}
