/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:38:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/21 11:18:01 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoil(char *nptr)
{
	long int	i;
	long int	result;

	i = 0;
	result = 0;
	if (!nptr)
		return (0);
	if (nptr[0] == '-')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9' && result < 2147483647)
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	if (result > 2147483647)
		return (-1);
	return (result);
}

int	check_ifnumber(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i++][0] == '\0')
			return (-1);
	}
	i = 0;
	while (++i < argc)
	{
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '-' && argv[i][j - 1] != '-' && j == 0)
				j++;
			if ((argv[i][j] >= '0' && argv[i][j] <= '9'))
				j++;
			else
				return (-1);
		}
		j = 0;
	}
	return (0);
}

long long	get_time(void)
{
	t_time		current;
	long long	time;

	time = gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000 + current.tv_usec / 1000);
	return (time);
}

long long	get_elapsed_time(t_philo *philo)
{
	long long	time_elapsed;

	time_elapsed = get_time() - philo->creation_time;
	return (time_elapsed);
}

void	ft_print(t_philo *philo, char *msg)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&philo->info->lock);
	if (philo->info->game_over == 0)
	{
		printf("%lld %d %s\n", get_elapsed_time(philo), philo->id, msg);
		pthread_mutex_unlock(&philo->info->lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->lock);
		return ;
	}
}
