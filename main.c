/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:05:01 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/19 22:15:51 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "headers/philo.h"

void	parsing_argv(int argc, char **argv, t_dat *dat)
{
	dat->total_ph = atoi(argv[1]);
	dat->tdie = atol(argv[2]);
	dat->teat = atol(argv[3]);
	dat->tsleep = atol(argv[4]);
	dat->eat_max = 1;
	if (argc == 6)
		dat->eat_max = atoi(argv[4]);
	if (!dat->total_ph || !dat->tdie || !dat->teat
		|| !dat->tsleep || !dat->eat_max)
		print_exit("Error\nLos argumentos son erroneos.");
}

int	main(int argc, char **argv)
{
	t_dat dat;

	if (argc == 5 || argc == 6)
		parsing_argv(argc, argv, &dat);
	else
		print_exit("Error\nNumero de argumentos invalido.");
	//init_nodes();
}

