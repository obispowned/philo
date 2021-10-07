/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:30:30 by agutierr          #+#    #+#             */
/*   Updated: 2021/09/18 19:55:52 by agutierr         ###   ########.fr       */
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
		/*while (((philo->fork_flags[philo->lfork] != 0) && (philo->fork_flags[philo->rfork] != 0))  ||(philo->caronte_comes != 0))
		{
			caronte_comes(philo);
			//dead_check(philo);
		}*/
		philo->fork_flags[philo->lfork] = 1;
		philo->fork_flags[philo->rfork] = 1;
		take_fork(philo);
	}
}

/*void	caronte_comes(t_ph *philo)
{
	uint64_t		timer;
	
	timer = start_clock(0);
	if ((timer - philo->last_eat) >= (philo->tdie - philo->tdie / 4))
		philo->caronte_comes = 1;
}*/

void	max_eats_check(t_ph *philo)
{
	if (philo->eat_count == philo->total_eats)
		(*(philo->full_eats))+=1;
}

/*void	dead_check(t_ph *philo)
{
	uint64_t	timer;

	timer = start_clock();
	if ((timer - philo->last_eat) > philo->tdie)
	{
		printer(RED, timer - philo->start, philo, "is dead");
		exit(0);
	}
}*/

void	take_fork(t_ph *philo)
{
	pthread_mutex_lock(philo->llfork);
	printer(YELLOW, start_clock(philo->start), philo, "has taken left fork");
	pthread_mutex_lock(philo->rrfork);
	printer(YELLOW, start_clock(philo->start), philo, "has taken right fork");
}
