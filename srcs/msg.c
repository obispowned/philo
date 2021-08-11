/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:53:19 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/11 18:34:05 by agutierr         ###   ########.fr       */
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

void	print_exit(char *str)
{
	putstr(str);
	exit (0);
}

int	ret_error(char *str)
{
	putstr(str);
	return (0);
}

void	printer(char *color, int philo_n, int fork_n, char *msg)
{
	if (fork_n == 999999999)
		printf("%s(%d) %s.\n", color, philo_n, msg);
	else
		printf("%s(%d) %s (%d)\n", color, philo_n, msg, fork_n);
}
