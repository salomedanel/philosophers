/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:34:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/16 18:02:16 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_endofgame(t_info *info)
{
	pthread_mutex_lock(&info->lock);
	if (check_death(info) == 1 || check_nbmeals(info) == 1)
	{
		pthread_mutex_unlock(&info->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&info->lock);
		return (0);
	}
}

int	check_death(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if ((get_elapsed_time(&info->philo[i])
				- info->philo[i].last_meal) > info->t_die)
		{
			info->game_over = 1;
			printf("%lld %d %s\n", get_elapsed_time(&info->philo[i]),
				info->philo[i].id, MSD);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_nbmeals(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (info->n_meals_todo <= info->n_meals_done && info->n_meals_todo > 0)
		{
			info->game_over = 1;
			printf("All meals done. Nb meals: %d\n", info->n_meals_done
				/ info->nb_philo);
			return (1);
		}
		i++;
	}
	return (0);
}
