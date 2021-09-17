/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:30:30 by agutierr          #+#    #+#             */
/*   Updated: 2021/09/17 16:33:02 by agutierr         ###   ########.fr       */
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
		while (((philo->fork_flags[philo->lfork] != 0) && (philo->fork_flags[philo->rfork] != 0))  ||(philo->caronte_comes != 0))
		{
			caronte_comes(philo);
			//dead_check(philo); /*si quito esto peta*/
		}
		philo->fork_flags[philo->lfork] = 1;
		philo->fork_flags[philo->rfork] = 1;
		take_fork(philo);
	}
}

void	caronte_comes(t_ph *philo)
{
	uint64_t		timer;
	
	timer = start_clock();
	if ((timer - philo->last_eat) >= (philo->tdie - philo->tdie / 4))
		philo->caronte_comes = 1;
}

void	max_eats_check(t_ph *philo)
{
	if (philo->eat_count == philo->total_eats)
		(*(philo->flag_eat_max))++;
	if (*(philo->flag_eat_max) == philo->total_ph)
		print_exit("\n");
}

void	dead_check(t_ph *philo)
{
	uint64_t	timer;

	timer = start_clock();
	if ((timer - philo->last_eat) > philo->tdie)
	{
		printer(RED, timer - philo->start, philo, "is dead");
		exit(0);
	}
}

void	take_fork(t_ph *philo)
{	
	uint64_t	timer;

	timer = start_clock();
	pthread_mutex_lock(philo->llfork);
	printer(YELLOW, timer - philo->start, philo, "has taken left fork");
	pthread_mutex_lock(philo->rrfork);
	timer = start_clock();
	printer(YELLOW, timer - philo->start, philo, "has taken right fork");
}
