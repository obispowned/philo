/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 20:30:30 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/09 21:05:18 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	take_fork_prior(t_ph *philo)
{
	if (philo->caronte_comes == 1 || philo->eat_count == 0)
		take_fork(philo);
	else
	{
		ft_usleep(0);
		take_fork(philo);
	}
}

void	caronte_comes(t_ph *philo)
{
	if ((ft_time(0) - philo->last_eat) <= philo->tdie / 2)
	{
		philo->caronte_comes = 1;
		printer(RED, philo->ph_n, 999999999,
			"Caronte en su canoa esta en camino a por tu alma");
	}
	else
		ft_usleep(0);
}

void	max_eats_check(t_ph *philo)
{
	if (philo->eat_count == philo->total_eats)
	{
		printf("philo %d, count %d, total_eat: %d ",
			philo->ph_n, philo->eat_count, philo->total_eats);
		print_exit("Se acabó la comida.\n");
	}
}

void	dead_check(t_ph *philo, uint64_t	aux_time)
{
	uint64_t	timer;

	pthread_mutex_lock(philo->deadmtx);
	if ((aux_time - philo->last_eat) > philo->tdie)
	{
		timer = ft_time(0);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(RED, philo->ph_n, 999999999, "is dead");
		exit (0);
	}
	else
		pthread_mutex_unlock(philo->deadmtx);
}

void	take_fork(t_ph *philo)
{	
	if (philo->ph_n == philo->total_ph)
	{
		pthread_mutex_lock(philo->rrfork);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n, philo->rfork, "has taken right fork");
		pthread_mutex_lock(philo->llfork);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n,
			philo->lfork, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->llfork);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n, philo->lfork, "has taken left fork");
		pthread_mutex_lock(philo->rrfork);
		printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
		printer(YELLOW, philo->ph_n,
			philo->rfork, "has taken right fork");
	}
}
