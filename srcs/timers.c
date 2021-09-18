/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:52:52 by agutierr          #+#    #+#             */
/*   Updated: 2021/09/18 18:41:58 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = start_clock(0);
	while (start_clock(start) < miliseconds)
		usleep(1);
}

uint64_t	start_clock(uint64_t start)
{
	struct timeval	aux_clock;
	uint64_t	ret;

	gettimeofday(&aux_clock, NULL);
	ret = (aux_clock.tv_sec * 1000) + (aux_clock.tv_usec / 1000);
	ret -= start;
	return (ret);
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
