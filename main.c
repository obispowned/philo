/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/08 21:30:10 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

void	take_fork(t_ph *philo)
{	
	if (philo->total_ph % 2 == 0)
	{
		while (philo->ph_n % 2 == 0 && *(philo->phase_num) != 0)
			;
		while ((philo->ph_n % 2 != 0) && (*(philo->phase_num) != 1))
			;
	}
	else
	{
		while (philo->ph_n % 2 == 0 && ((*(philo->phase_num)) != 0))
			;
		while ((philo->ph_n % 2 != 0) && (philo->ph_n != philo->total_ph) && (*(philo->phase_num) != 1))
			;
		while ((philo->ph_n == philo->total_ph) && (*(philo->phase_num) != 2))
			;
	}
	pthread_mutex_lock(philo->llfork);
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printer(YELLOW, philo->ph_n, philo->lfork, "has taken left fork");
	pthread_mutex_lock(philo->rrfork);
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printer(YELLOW, philo->ph_n,
		philo->rfork, "has taken right fork");
}

uint64_t	time_to_eat(t_ph *philo)
{
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printer(GREEN, philo->ph_n, 999999999, "eats...");
	ft_usleep(philo->teat);
	philo->eat_count++; 
	pthread_mutex_unlock(philo->rrfork);
	pthread_mutex_unlock(philo->llfork);
	if (philo->ph_n % 2 == 0)
		*(philo->phase_num) = 1;
	else if ((philo->ph_n % 2 != 0) && philo->total_ph % 2 == 0)
		*(philo->phase_num) = 0;
	else if ((philo->ph_n % 2 != 0) && (philo->ph_n != philo->total_ph) && philo->total_ph % 2 != 0)
		*(philo->phase_num) = 2;
	else if ((philo->ph_n == philo->total_ph) && (philo->total_ph % 2 != 0))
		*(philo->phase_num) = 0;
	return (0);
}

uint64_t	time_to_sleep(t_ph *philo)
{
	uint64_t timer;
	
	timer = ft_time(0);
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printf("%s(%d) is sleeping zZ zZzZ\n", MAGENTA, philo->ph_n);
	ft_usleep(philo->tsleep);
	return (0);
}	

uint64_t	time_to_think(t_ph *philo)
{
	printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
	printf("%s(%d) is thinking... var: %d\n", WHITE, philo->ph_n, *(philo->phase_num));
	return (0);
}	

void	*rutine(void *arg)
{
	t_ph		*philo;
	uint64_t	aux_time;
	uint64_t	timer;

	philo = (t_ph *)arg;
	philo->last_eat = ft_time(0);
	/*if (philo->ph_n % 2 == 0 || philo->ph_n == philo->total_ph) //implementacion kevin
	{	
		printf("pasa por aqui %d\n", philo->ph_n);
		ft_usleep(philo->teat);									//implementacion kevin
	}*/
	while (1)
	{
		if (philo->caronte_comes == 1 || philo->eat_count == 0)
			take_fork(philo);
		else if (philo->ph_n % 2 == 0)
			take_fork(philo);
		else if (philo->ph_n % 2 != 0 && philo->ph_n != philo->total_ph)
			take_fork(philo);
		else if (philo->ph_n == philo->total_ph)
			take_fork(philo);
		else
		{
			ft_usleep(0);
			take_fork(philo);
		}
		aux_time = ft_time(0);
		if ((aux_time - philo->last_eat) >= philo->tdie)
		{
			timer = ft_time(0);
			printf("%s| %-8llu ms | ", CYAN, ft_time(0) - philo->start);
			printer(RED, philo->ph_n, 999999999, "is dead");
			exit (0);
		}
		philo->last_eat = ft_time(0);
		philo->caronte_comes = 0;
		time_to_eat(philo);
		if (philo->eat_count == philo->total_eats)
		{
			printf("philo %d, count %d, total_eat: %d ", philo->ph_n, philo->eat_count, philo->total_eats);
			print_exit("Se acabó la comida.\n");
		}
		time_to_sleep(philo);
		time_to_think(philo);
		//printf("\n\n%llu\n\n", (ft_time(0) - philo->last_eat));
		if ((ft_time(0) - philo->last_eat) <= philo->tdie / 2)
		{
			philo->caronte_comes = 1;
			printer(RED, philo->ph_n, 999999999, "Caronte en su canoa esta en camino a por tu alma");
		}
		else
			ft_usleep(0);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dat			dat;
	pthread_mutex_t	*mtx;

	if (argc < 5 || argc > 6)
		print_exit("Error\nNumero de argumentos invalido.");
	parsing_argv(argc, argv, &dat);
	mtx = fill_structs(&dat);
	dat.begin = start_clock();
	create_threads(&dat);
	run_threads(&dat);
	turbofree(mtx, &dat);
	return (0);
}
