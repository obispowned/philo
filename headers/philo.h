/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:02:17 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/09 19:25:11 by agutierr         ###   ########.fr       */
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
# define RESET_COLOR "\x1b[m"

# define ON 1
# define OFF 0

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
	int				*full_eats;
	int				*banquet;
	int				*fork_flags;
	int				lfork;
	int				rfork;
	pthread_mutex_t	*llfork;
	pthread_mutex_t	*rrfork;
	pthread_mutex_t	*mprint;
	int				*flag_eat_max;
}					t_ph;

typedef struct s_dat
{
	unsigned int	total_ph;
	uint64_t		begin;
	uint64_t		tdie;
	uint64_t		teat;
	uint64_t		tsleep;
	int				banquet;
	int				full_eat;
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
int				ret_error(char *str);
void			printer(char *color, t_ph *philo, char *msg);
int				print_error(char *str);

/*
*  free.c
*/
void			double_kill(char **str);
void			ace(char *str, ...);

/*
*  fill_nd_parse.c
*/
int				parsing_argv(int argc, char **argv, t_dat *dat);
pthread_mutex_t	*fill_structs(t_dat *dat);
void			fill_struct_for_normi(t_dat *dat, pthread_mutex_t
					*mtx, int *forky_flag, pthread_mutex_t *dead);

/*
**	timers.c
*/
uint64_t		start_clock(void);
void			ft_usleep(uint64_t miliseconds);
void			ft_usleep2(int numofphilos, uint64_t milliseconds);
int				ft_time(int start);
/*
**	create threads
*/
void			create_threads(t_dat *dat);
void			run_threads(t_dat *dat);
void			turbofree(t_dat *dat, pthread_mutex_t *mtx);

void			take_fork(t_ph *philo);
uint64_t		time_to_eat(t_ph *philo);
uint64_t		time_to_sleep(t_ph *philo);
uint64_t		time_to_think(t_ph *philo);
void			*rutine(void *arg);

void			caronte_comes(t_ph *philo);
void			max_eats_check(t_ph *philo);
void			status_check(t_ph *philo);
void			take_fork(t_ph *philo);
void			take_fork_prior(t_ph *philo);

int				strafing_killer(t_dat *dat, int i);
int				dead_checker(t_dat *dat);

#endif
