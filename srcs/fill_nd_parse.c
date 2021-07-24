/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nd_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:45:38 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/20 18:02:33 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/philo.h"

void	parsing_argv(int argc, char **argv, t_dat *dat)
{
	if (argc == 6)
	{
		if (!isallnum(argv[5]))
			print_exit("Error\nYou must use only integer numbers!");
		dat->eat_max = (uint64_t)ft_atol(argv[5]);
	}
	else
		dat->eat_max = 0;
	if (!isallnum(argv[1]) || !isallnum(argv[2])
		|| !isallnum(argv[3]) || !isallnum(argv[4]))
		print_exit("Error\nYou must use only integer numbers!");
	dat->total_ph = (unsigned int)ft_atol(argv[1]);
	dat->tdie = (uint64_t)ft_atol(argv[2]);
	dat->teat = (uint64_t)ft_atol(argv[3]);
	dat->tsleep = (uint64_t)ft_atol(argv[4]);
	dat->eat_max = 1;
	if (!dat->total_ph || !dat->tdie || !dat->teat
		|| !dat->tsleep || !dat->eat_max)
		print_exit("Error\nBad arguments");
}

void	fill_structs(t_dat *dat)
{
	int i;

	i = 0;
	mtx = malloc(sizeof(mtx) * dat->total_ph);
	while (i < dat->total_ph)
	{
		pthread_mutex_init(&mtx[i], NULL);
		pthread_mutex_unlock(&mtx[i]);
		dat->philos[i].ph_n = i + 1;
		dat->philos[i].tdie = dat->tdie;
		dat->philos[i].teat = dat->teat;
		dat->philos[i].tsleep = dat->tsleep;
		dat->philos[i].eat_max = dat->eat_max;
		dat->philos[i].lfork = i;
		if (i == 0)
			dat->philos[i].rfork = dat->total_ph;
		else
			dat->philos[i].rfork = i - 1;
		dat->philos[i].llfork = &mtx[dat->philos[i].lfork];
		dat->philos[i].rrfork = &mtx[dat->philos[i].rfork];
		i++;
	}
}
