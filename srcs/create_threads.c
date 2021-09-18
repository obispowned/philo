/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:32:55 by agutierr          #+#    #+#             */
/*   Updated: 2021/09/18 17:01:06 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	create_threads(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->total_ph)
	{
		(dat->philos[i]).start = dat->begin;
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

void	turbofree(t_dat *dat)
{
	free(dat->philos);
}
