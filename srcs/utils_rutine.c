/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:30:30 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/08 20:38:26 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	take_fork_prior(t_ph *philo)
{
	if (philo->eat_count == 0)
	{
		philo->fork_flags[philo->lfork] = 1;
		philo->fork_flags[philo->rfork] = 1;
		take_fork(philo);
	}
	else
	{
		philo->fork_flags[philo->lfork] = 1;
		philo->fork_flags[philo->rfork] = 1;
		take_fork(philo);
	}
}

void	max_eats_check(t_ph *philo)
{
	if (philo->eat_count == philo->total_eats)
		(*(philo->full_eats)) += 1;
}

void	take_fork(t_ph *philo)
{
	pthread_mutex_lock(philo->llfork);
	printer(YELLOW, start_clock(philo->start), philo, "has taken left fork");
	pthread_mutex_lock(philo->rrfork);
	printer(YELLOW, start_clock(philo->start), philo, "has taken right fork");
}
