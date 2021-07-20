/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:02:17 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/20 18:04:35 by agutierr         ###   ########.fr       */
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
	pthread_t		philos;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		tsleep;
	uint64_t		eat_max;
	int				action;		//2 comer 1 dormir 0 pensar
	pthread_mutex_t	lock;
	pthread_mutex_t	special_lock;
}					t_ph;

typedef struct s_dat
{
	unsigned int	total_ph;
	uint64_t		begin;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		tsleep;
	unsigned int	eat_max;
	t_ph			*philos;
	pthread_mutex_t mtx;
}					t_dat;

/*
*	utils.c
*/
int	ft_atoi2(int sign);
int	ft_atoi(const char *str);
long long	ft_atol(const char *str);
int		isallnum(char *str);

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

/*
*  fill_nd_parse.c
*/
void	parsing_argv(int argc, char **argv, t_dat *dat);
void	fill_structs(t_dat *dat);

#endif
