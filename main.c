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
void	take_fork(void *arg)
{

}

void	create_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_create(&(dat->philos[i].philos), NULL, &take_fork, dat->philos);
		i++;
	}
}

void	create_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_join(&(dat->philos[i].philos), NULL);
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
}

