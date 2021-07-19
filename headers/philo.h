/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:02:17 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/19 20:35:53 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_ph
{
	unsigned int	ph_n;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		tsleep;
	uint64_t		eat_max;
	int				action;		//2 comer 1 dormir 0 pensar
	struct s_ph		*next;
}				t_ph;

typedef struct s_dat
{
	unsigned int	total_ph;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		tsleep;
	unsigned int	eat_max;
	t_ph			**philo;
}				t_dat;

/*
*  msg.c
*/
void	putstr(char *str);
void	print_exit(char *str);
int		ret_error(char *str);

/*
*  free.c
*/
void			double_kill(char **str);
void			ace(char *str, ...);

#endif
