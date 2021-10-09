/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:15:52 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/09 19:16:34 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

uint64_t	time_to_eat(t_ph *philo)
{
	if (*philo->banquet == 1)
	{
		take_fork_prior(philo);
	}
	philo->last_eat = start_clock();
	printer(GREEN, philo, "is eating...");
	ft_usleep2(philo->total_ph, philo->teat);
	philo->eat_count++;
	pthread_mutex_unlock(philo->llfork);
	pthread_mutex_unlock(philo->rrfork);
	max_eats_check(philo);
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	if (*philo->banquet == 1)
	{
		printer(MAGENTA, philo, "is sleeping zZzZzZ.");
		ft_usleep2(philo->total_ph, philo->teat);
	}
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	if (*philo->banquet == 1)
		printer(WHITE, philo, "is thinking...");
	usleep(50);
	return (0);
}	
