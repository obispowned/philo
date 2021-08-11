/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:52:52 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/11 20:31:26 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;
	uint64_t	i;

	i = 0;
	start = start_clock();
	while (i < miliseconds)
	{
		usleep(1);
		i = start_clock() - start;
	}
}

uint64_t	start_clock(void)
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((uint64_t)((aux_clock.tv_usec / 1000)) + (aux_clock.tv_sec * 1000));
}

/*
** FUNCION PARA MOSTRAR LA HORA ACTUAL
*/
void	current_time(void)
{
	long			hms;
	struct timeval	tv;
	int				sec_per_DHM[3];

	sec_per_DHM[0] = 86400;
	sec_per_DHM[1] = 3600;
	sec_per_DHM[2] = 60;
	gettimeofday(&tv, NULL);
	hms = tv.tv_sec % sec_per_DHM[0];
	hms = (hms + sec_per_DHM[0]) % sec_per_DHM[0];
	printf("Son las: %ld:%02ld:%02ld\n", (hms / sec_per_DHM[1]) + 2,
		((hms % sec_per_DHM[1]) / sec_per_DHM[2]),
		(hms % sec_per_DHM[1]) % sec_per_DHM[2]);
}
