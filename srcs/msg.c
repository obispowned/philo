/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:07:34 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/20 17:01:58 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/philo.h"

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

int		ret_error(char *str)
{
	putstr(str);
	return (0);
}

void	printer(char *color, int philo_n, int fork_n, char *msg)
{
	printf("%sPhilo [%d], %s (%d)\n", color, philo_n-1, msg, fork_n);
}
