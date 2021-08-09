/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nd_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:45:38 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/09 19:18:49 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	parsing_argv(int argc, char **argv, t_dat *dat)
{
	dat->total_eats = -1;
	if (argc == 6)
	{
		if (!argv[5] || !isallnum(argv[5]))
			print_exit("Error\nYou must use only integer numbers!");
		dat->total_eats = (uint64_t)ft_atol(argv[5]);
	}
	if (!isallnum(argv[1]) || !isallnum(argv[2])
		|| !isallnum(argv[3]) || !isallnum(argv[4]))
		print_exit("Error\nYou must use only integer numbers!");
	dat->total_ph = (unsigned int)ft_atol(argv[1]);
	dat->tdie = (uint64_t)ft_atol(argv[2]);
	dat->teat = (uint64_t)ft_atol(argv[3]);
	dat->tsleep = (uint64_t)ft_atol(argv[4]);
	if (!dat->total_ph || !dat->tdie || !dat->teat
		|| !dat->tsleep)
		print_exit("Error\nBad arguments");
}

pthread_mutex_t	*fill_structs(t_dat *dat)
{
	int				i;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	dead;

	i = -1;
	dat->philos = malloc(sizeof(t_ph) * dat->total_ph);
	mtx = malloc(sizeof(pthread_mutex_t) * dat->total_ph);
	pthread_mutex_init(&dead, NULL);
	pthread_mutex_unlock(&dead);
	while (++i < dat->total_ph)
	{
		pthread_mutex_init(&mtx[i], NULL);
		pthread_mutex_unlock(&mtx[i]);
		dat->philos[i].ph_n = i + 1;
		dat->philos[i].tdie = dat->tdie;
		dat->philos[i].teat = dat->teat;
		dat->philos[i].tsleep = dat->tsleep;
		dat->philos[i].eat_count = 0;
		dat->philos[i].lfork = i;
		dat->philos[i].total_eats = dat->total_eats;
		dat->philos[i].last_eat = 0;
		dat->philos[i].caronte_comes = 0;
		dat->philos[i].total_ph = dat->total_ph;
		if (i == 0)
			dat->philos[i].rfork = dat->total_ph - 1;
		else
			dat->philos[i].rfork = i - 1;
		dat->philos[i].llfork = &(mtx[dat->philos[i].lfork]);
		dat->philos[i].rrfork = &(mtx[dat->philos[i].rfork]);
		dat->philos[i].deadmtx = &dead;
	}
	return (mtx);
}
