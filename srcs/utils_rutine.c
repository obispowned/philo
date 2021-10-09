/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:30:30 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/09 19:12:56 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	take_fork_prior(t_ph *philo)
{
	take_fork(philo);
}

void	max_eats_check(t_ph *philo)
{
	if (philo->eat_count == philo->total_eats)
		(*(philo->full_eats)) += 1;
}

void	take_fork(t_ph *philo)
{
	if ((philo->total_ph % 2 != 0) && (philo->ph_n == philo->total_ph - 1))
	{
		pthread_mutex_lock(philo->rrfork);
		printer(YELLOW, philo, "has taken right fork");
		pthread_mutex_lock(philo->llfork);
		printer(YELLOW, philo, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		printer(YELLOW, philo, "has taken left fork");
		pthread_mutex_lock(philo->rrfork);
		printer(YELLOW, philo, "has taken right fork");
	}
}
