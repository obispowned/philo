/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/08 21:56:50 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*rutine(void *arg)
{
	t_ph		*philo;

	philo = (t_ph *)arg;
	if (philo->ph_n % 2 == 0)
		ft_usleep(philo->teat - 10);
	if (((philo->total_ph % 2 != 0) && (philo->total_ph != 1))
		&& ((philo->ph_n == philo->total_ph - 1)))
		ft_usleep(philo->teat + 10);
	while (*philo->banquet == ON)
	{
		take_fork_prior(philo);
		philo->caronte_comes = 0;
		time_to_eat(philo);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return ((void*)0);
}

void	printerd(char *color, uint64_t timer, t_ph *philo, char *msg)
{
	pthread_mutex_lock(philo->mprint);
	printf("%s| %-8llu ms | %s(%d) %s.\n", CYAN, timer, color, philo->ph_n, msg);
}

int	strafing_killer(t_dat *dat, int i)
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
		{
			return (strafing_killer(dat, i));
		}
		if (*dat->philos[0].full_eats == dat->total_ph)
		{
			dat->banquet = OFF;
			return (1);
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
	int				i;
	pthread_mutex_t	*mtx;

	i = 0;
	if (argc < 5 || argc > 6)
		return (print_error("Error\nNumero de argumentos invalido."));
	if (!parsing_argv(argc, argv, &dat))
		return (0);
	mtx = fill_structs(&dat);
	create_threads(&dat);
	if (status_checker(&dat) == 0 && dat.total_ph > 1)
	{
		run_threads(&dat);
	}
	else if (status_checker(&dat) == 1 && dat.total_ph > 1)
	{
		run_threads(&dat);
	}
	while (i < dat.total_ph)
	{ 
		pthread_detach(dat.philos[i].philos);
		i++;
	}
	turbofree(&dat, mtx);
	return (0);
}
