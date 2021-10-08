/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nd_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:45:38 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/08 20:45:39 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	parsing_argv(int argc, char **argv, t_dat *dat)
{
	dat->total_eats = -1;
	if (argc == 6)
	{
		if (!argv[5] || !isallnum(argv[5]))
			return (print_error("Error\nYou must use only integer numbers!"));
		dat->total_eats = (uint64_t)ft_atol(argv[5]);
	}
	if (!isallnum(argv[1]) || !isallnum(argv[2])
		|| !isallnum(argv[3]) || !isallnum(argv[4]))
		return (print_error("Error\nYou must use only integer numbers!"));
	dat->total_ph = (unsigned int)ft_atol(argv[1]);
	dat->tdie = (uint64_t)ft_atol(argv[2]);
	dat->teat = (uint64_t)ft_atol(argv[3]);
	dat->tsleep = (uint64_t)ft_atol(argv[4]);
	if (!dat->total_ph || !dat->tdie || !dat->teat
		|| !dat->tsleep)
		return (print_error("Error\nBad arguments"));
	return (1);
}

void	fill_structs2(t_dat *dat, int i)
{
	int	flag_eats;

	flag_eats = 0;
	dat->begin = start_clock(0);
	dat->philos[i].ph_n = i;
	dat->philos[i].tdie = dat->tdie;
	dat->philos[i].teat = dat->teat;
	dat->philos[i].tsleep = dat->tsleep;
	dat->philos[i].eat_count = 0;
	dat->philos[i].lfork = i;
	if (i == 0)
		dat->philos[i].rfork = dat->total_ph - 1;
	else
		dat->philos[i].rfork = i - 1;
	dat->philos[i].total_eats = dat->total_eats;
	dat->philos[i].last_eat = dat->begin;
	dat->philos[i].caronte_comes = 0;
	dat->philos[i].total_ph = dat->total_ph;
	dat->philos[i].flag_eat_max = &flag_eats;
}

void	fill_forks(t_dat *dat, int *forky_flag)
{
	int	i;

	i = 0;
	dat->full_eat = 0;
	dat->banquet = ON;
	while (i < dat->total_ph)
	{
		forky_flag[i] = 0;
		i++;
	}
	i = 0;
	while (i < dat->total_ph)
	{
		dat->philos[i].fork_flags = forky_flag;
		dat->philos[i].full_eats = &(dat->full_eat);
		dat->philos[i].banquet = &dat->banquet;
		i++;
	}
}

void	fill_struct_for_normi(t_dat *dat, pthread_mutex_t *mtx,
	int *forky_flag, pthread_mutex_t *dead)
{
	int	i;

	i = -1;
	while (++i < dat->total_ph)
	{
		fill_structs2(dat, i);
		dat->philos[i].llfork = &(mtx[dat->philos[i].lfork]);
		dat->philos[i].rrfork = &(mtx[dat->philos[i].rfork]);
		dat->philos[i].mprint = dead;
		dat->philos[i].start = dat->begin;
		forky_flag[i] = 0;
	}
}

pthread_mutex_t	*fill_structs(t_dat *dat)
{
	int				i;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*dead;
	int				*forky_flag;

	i = -1;
	dat->philos = malloc(sizeof(t_ph) * dat->total_ph);
	forky_flag = malloc(sizeof(int) * dat->total_ph);
	mtx = malloc(sizeof(pthread_mutex_t) * dat->total_ph);
	dead = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&dead[0], NULL);
	pthread_mutex_unlock(&dead[0]);
	while (++i < dat->total_ph)
	{
		pthread_mutex_init(&mtx[i], NULL);
		pthread_mutex_unlock(&mtx[i]);
	}
	fill_struct_for_normi(dat, mtx, forky_flag, dead);
	fill_forks(dat, forky_flag);
	return (mtx);
}
