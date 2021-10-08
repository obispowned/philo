/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:53:19 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/08 20:40:19 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	putstr(char *str)
{
	while (*str)
	{
		write (1, str, 1);
		str++;
	}
}

int	print_error(char *str)
{
	putstr(str);
	return (0);
}

int	ret_error(char *str)
{
	putstr(str);
	return (0);
}

void	printer(char *color, uint64_t timer, t_ph *philo, char *msg)
{
	if (*philo->banquet == ON)
	{
		if (strcmp(msg, "is dead") == 0)
			*philo->banquet = OFF;
		pthread_mutex_lock(philo->mprint);
		printf("%s| %-8llu ms | %s(%d) %s.\n", CYAN, timer,
			color, philo->ph_n, msg);
		printf("%s", RESET_COLOR);
		pthread_mutex_unlock(philo->mprint);
	}
}
