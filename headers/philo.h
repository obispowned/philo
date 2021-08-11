/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:02:17 by agutierr          #+#    #+#             */
/*   Updated: 2021/08/11 18:27:43 by agutierr         ###   ########.fr       */
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

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

typedef struct s_ph
{
	unsigned int	total_ph;
	unsigned int	ph_n;
	pthread_t		philos;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		last_eat;
	uint64_t		tsleep;
	uint64_t		start;
	int				caronte_comes;
	int				eat_count;
	int				total_eats;
	int				*fork_flags;
	int				lfork;
	int				rfork;
	pthread_mutex_t	*llfork;
	pthread_mutex_t	*rrfork;
	pthread_mutex_t	*mprint;
	int				*flag_eat_max; //cada vez que un filo llega a eat_max, se suma 1
								//cuando el valor llegue al numero de ph que hay, fin de programa
}					t_ph;

typedef struct s_dat
{
	unsigned int	total_ph;
	uint64_t		begin;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		tsleep;
	unsigned int	total_eats;
	t_ph			*philos;
}					t_dat;

/*
*	utils.c
*/
int				ft_atoi2(int sign);
int				ft_atoi(const char *str);
long long		ft_atol(const char *str);
int				isallnum(char *str);

/*
*  msg.c
*/
void			putstr(char *str);
void			print_exit(char *str);
int				ret_error(char *str);
void			printer(char *color, int philo_n, int fork_n, char *msg);

/*
*  free.c
*/
void			double_kill(char **str);
void			ace(char *str, ...);

/*
*  fill_nd_parse.c
*/
void			parsing_argv(int argc, char **argv, t_dat *dat);
pthread_mutex_t	*fill_structs(t_dat *dat);

/*
**	timers.c
*/
void			ft_usleep(uint64_t miliseconds);
uint64_t		ft_time(uint64_t start);
uint64_t		start_clock(void);

/*
**	create threads
*/
void			create_threads(t_dat *dat);
void			run_threads(t_dat *dat);
void			turbofree(pthread_mutex_t *mtx, t_dat *dat);

void			take_fork(t_ph *philo);
uint64_t		time_to_eat(t_ph *philo);
uint64_t		time_to_sleep(t_ph *philo);
uint64_t		time_to_think(t_ph *philo);
void			*rutine(void *arg);

void			caronte_comes(t_ph *philo);
void			max_eats_check(t_ph *philo);
void			dead_check(t_ph *philo, uint64_t	aux_time);
void			take_fork(t_ph *philo);
void			take_fork_prior(t_ph *philo);

#endif
