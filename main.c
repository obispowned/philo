/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/09/18 19:31:26 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

uint64_t	time_to_eat(t_ph *philo)
{
	philo->last_eat = start_clock(0);
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
	printer(MAGENTA, start_clock(philo->start), philo, "is sleeping zZzZzZ.");
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	printer(WHITE, start_clock(philo->start), philo, "is thinking...");
	return (0);
}	

void	*rutine(void *arg)
{
	t_ph		*philo;
	
	philo = (t_ph *)arg;
	if (philo->total_ph % 2 == 0 && philo->ph_n % 2 == 0)
		ft_usleep(philo->teat);
	if (((philo->total_ph % 2 != 0) && (philo->total_ph != 1)) && ((philo->ph_n == philo->total_ph -1) || philo->total_ph % 2 == 0))
		ft_usleep(philo->teat);
	while (*philo->banquet == ON)
	{
		take_fork_prior(philo);
		//philo->caronte_comes = 0;
		time_to_eat(philo);
		time_to_sleep(philo);
		time_to_think(philo);
		//caronte_comes(philo);
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
	printer(RED, start_clock(dat->begin), &(dat->philos[i]), "is dead");
	return (0);
}

int	status_checker(t_dat *dat)
{
	int	i;

	i = 0;
	while (1)
	{
		if (start_clock(dat->philos[i].last_eat) > dat->tdie)
			return (strafing_killer(dat, i));
		if (*dat->philos[0].full_eats == dat->total_ph)
		{
			dat->banquet = OFF;
			return(1);
		}
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
	if (status_checker(&dat) == 0 && dat.total_ph > 1)
	{
		run_threads(&dat);
	}
	else if (status_checker(&dat) == 1 && dat.total_ph > 1)
	{
		run_threads(&dat);
	}
	turbofree(&dat);
	return (0);
}
