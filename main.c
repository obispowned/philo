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
/*void	take_fork(void *arg)
{
	t_ph *philo;

	philo = (t_ph *)arg;
	if (!philo->t->scythe_carrier)
	{
		pthread_mutex_lock(&philo->llock);
		if (philo->t->philos > 1)
			pthread_mutex_lock(&philo->rh->lock);
		pthread_mutex_lock(&philo->rh->special_lock);
		fork_acquisition(philo);
		food_consumption(philo);
		if (philo->t->philos > 1)
			pthread_mutex_unlock(&philo->rh->lock);
		pthread_mutex_unlock(&philo->lock);
		sweet_dreaming_and_thinking(philo);
	}
	else
		return (NULL);
	return (NULL);
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
		pthread_join(&(dat->philos[i].philos), NULL);
		i++;
	}
}*/


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
	/*dat.begin = fireee();
	printf("time %llu\n", dat.begin);
	sleep(1);
	printf("time %llu\n", dat.begin);*/
	//create_threads(&dat);
	//run_threads(&dat);
}

