/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:32:55 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/09 19:05:20 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	create_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_create(&(dat->philos[i].philos), NULL, rutine, &dat->philos[i]);
		i++;
	}
}

void	run_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		pthread_join(dat->philos[i].philos, NULL);
		i++;
	}
}

void	destroy_mutex(t_dat *dat, pthread_mutex_t *mtx)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(dat->philos[0].mprint);
	while (i < dat->total_ph)
	{
		pthread_mutex_destroy(&(mtx[i]));
		i++;
	}
}

void	turbofree(t_dat *dat, pthread_mutex_t *mtx)
{
	destroy_mutex(dat, mtx);
	free(dat->philos[0].fork_flags);
	free(mtx);
	free(dat->philos[0].mprint);
	free(dat->philos);
}
