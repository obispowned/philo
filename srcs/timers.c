/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:52:52 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/09 18:50:12 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_usleep(uint64_t miliseconds)
{
	int	start;

	start = ft_time(0);
	while (ft_time(start) < miliseconds)
	{
		usleep(1);
	}
}

void	ft_usleep2(int numofphilos, uint64_t milliseconds)
{
	uint64_t		time;
	uint64_t		end_ms;

	time = start_clock();
	end_ms = time + milliseconds;
	while (time < end_ms)
	{
		time = start_clock();
		usleep(numofphilos);
	}
}

int	ft_time(int start)
{
	int					current_time;
	struct timeval		aux_clock;

	gettimeofday(&aux_clock, NULL);
	current_time = (int)
		((aux_clock.tv_usec / 1000) + (aux_clock.tv_sec * 1000));
	return (current_time - start);
}

uint64_t	start_clock(void)
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((long long)((aux_clock.tv_usec / 1000))
		+ (aux_clock.tv_sec * 1000));
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
