/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:56:57 by agutierr          #+#    #+#             */
/*   Updated: 2021/07/19 20:35:29 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/philo.h"

void			killer(void	*str)
{
	free (str);
	str = NULL;
}

void			double_kill(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		killer(str[i]);
		i++;
	}
	free(str);
}

void			ace(char *str, ...)
{
	va_list		ap;

	va_start(ap, str);
	killer(str);
	while ((str = va_arg(ap, char *)))
		killer(str);
	va_end(ap);
}
