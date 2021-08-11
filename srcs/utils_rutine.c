/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:30:30 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/11 18:30:31 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	take_fork_prior(t_ph *philo)
{
	if (philo->caronte_comes == 1 || philo->eat_count == 0)
	{
		philo->fork_flags[philo->lfork] = 1;
		philo->fork_flags[philo->rfork] = 1;
		take_fork(philo);
	}
	else
	{
		while ((philo->fork_flags[philo->lfork] != 0) && (philo->fork_flags[philo->rfork] != 0))
			;
		philo->fork_flags[philo->lfork] = 1;
		philo->fork_flags[philo->rfork] = 1;
		take_fork(philo);
	}
}

void	caronte_comes(t_ph *philo)
{
	if ((ft_time(0) - philo->last_eat) >= (philo->tdie - philo->tdie / 4))
		philo->caronte_comes = 1;
	else
		ft_usleep(0);
}

void	max_eats_check(t_ph *philo)
{
	if (philo->eat_count == philo->total_eats)
		(*(philo->flag_eat_max))++;
	if (*(philo->flag_eat_max) == philo->total_ph)
		print_exit("\n");
}

void	dead_check(t_ph *philo, uint64_t	aux_time)
{
	uint64_t	timer;

	
	if ((aux_time - philo->last_eat) > philo->tdie)
	{
		timer = ft_time(0);
		pthread_mutex_lock(philo->mprint);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(RED, philo->ph_n, 999999999, "is dead");
		pthread_mutex_unlock(philo->mprint);
		exit (0);
	}
}

void	take_fork(t_ph *philo)
{	
	if (philo->ph_n == philo->total_ph)
	{
		pthread_mutex_lock(philo->rrfork);
		pthread_mutex_lock(philo->mprint);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n, philo->rfork, "has taken right fork");
		pthread_mutex_unlock(philo->mprint);
		pthread_mutex_lock(philo->llfork);
		pthread_mutex_lock(philo->mprint);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n,
			philo->lfork, "has taken left fork");
		pthread_mutex_unlock(philo->mprint);
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		pthread_mutex_lock(philo->mprint);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n, philo->lfork, "has taken left fork");
		pthread_mutex_unlock(philo->mprint);
		pthread_mutex_lock(philo->rrfork);
		pthread_mutex_lock(philo->mprint);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n,
			philo->rfork, "has taken right fork");
		pthread_mutex_unlock(philo->mprint);
	}
}
