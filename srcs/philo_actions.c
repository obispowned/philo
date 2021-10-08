/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:15:52 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/08 20:55:42 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

uint64_t	time_to_eat(t_ph *philo)
{
	philo->last_eat = start_clock(0);
	printer(GREEN, philo->last_eat - philo->start, philo, "eats...");
	ft_usleep(philo->teat);
	philo->eat_count++;
	pthread_mutex_unlock(philo->rrfork);
	pthread_mutex_unlock(philo->llfork);
	philo->fork_flags[philo->lfork] = 0;
	philo->fork_flags[philo->rfork] = 0;
	max_eats_check(philo);
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	printer(MAGENTA, start_clock(philo->start), philo, "is sleeping zZzZzZ.");
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	printer(WHITE, start_clock(philo->start), philo, "is thinking...");
	if ((philo->ph_n % 2) != 0)
		usleep(10);
	return (0);
}	
