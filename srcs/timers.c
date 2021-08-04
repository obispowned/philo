# include "../headers/philo.h"

void	ft_usleep(uint64_t miliseconds)
{
	uint64_t	start;

	start = ft_time(0);
	while (ft_time(start) < miliseconds)
	{
		usleep(1);
	}
}

uint64_t	ft_time(uint64_t start)
{
	uint64_t			current_time;
	struct timeval		aux_clock;

	gettimeofday(&aux_clock, NULL);
	current_time = (uint64_t)
		((aux_clock.tv_usec / 1000) + (aux_clock.tv_sec * 1000));
	return (current_time - start);
}

uint64_t	start_clock(void)
{
	struct timeval	aux_clock;

	gettimeofday(&aux_clock, NULL);
	return ((uint64_t)((aux_clock.tv_usec / 1000)) + (aux_clock.tv_sec * 1000));
}