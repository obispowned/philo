/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agutierr <agutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:53:59 by agutierr          #+#    #+#             */
/*   Updated: 2021/10/08 20:37:36 by agutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	isallnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t			i;
	char			*a;

	i = 0;
	a = ptr;
	while (i < n)
	{
		a[i] = (unsigned char)x;
		i++;
	}
	return (&a[0]);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned int	sum;

	sum = count * size;
	ptr = malloc(sum);
	if (!(ptr))
		return (0);
	ft_memset(ptr, 0, sum);
	return ((void *)ptr);
}
