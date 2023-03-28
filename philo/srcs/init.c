/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:45:17 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/21 11:29:53 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoil(argv[i]) == -1 || ft_atoil(argv[i]) == 0)
			return (ft_error(PBINT));
		i++;
	}
	if (check_ifnumber(argv, argc) == -1)
		return (ft_error(NDIGIT));
	return (0);
}

int	init_info(char **argv, int argc, t_info *info)
{
	if (check_arg(argv, argc) == 1)
		return (1);
	info->nb_philo = ft_atoil(argv[1]);
	info->t_die = ft_atoil(argv[2]);
	info->t_eat = ft_atoil(argv[3]);
	info->t_sleep = ft_atoil(argv[4]);
	info->n_meals_done = 0;
	info->game_over = 0;
	if (argc == 6)
	{
		info->n_meals_todo = ft_atoil(argv[5]) * info->nb_philo;
		if (info->n_meals_todo <= 0)
			return (ft_error(PBINT));
	}
	else
		info->n_meals_todo = 0;
	return (0);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->philo || !info->forks)
		return (ft_error(MLC));
	while (i < info->nb_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].creation_time = get_time();
		info->philo[i].last_meal = 0;
		info->philo[i].info = info;
		info->philo[i].l_fork_id = i;
		if (i == 0)
			info->philo[i].r_fork_id = info->nb_philo - 1;
		else
			info->philo[i].r_fork_id = i - 1;
		i++;
	}
	return (0);
}

int	launch_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->philo[i].thread, NULL, thread_routine,
				&info->philo[i]) != 0)
			return (ft_exit(info));
		i++;
	}
	return (0);
}

int	thread_init(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->lock, NULL) != 0)
		return (ft_exit(info));
	while (i < info->nb_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (ft_exit(info));
		i++;
	}
	launch_thread(info);
	usleep(info->t_eat * 1000);
	while (1)
	{
		if (check_endofgame(info) == 1)
		{
			return (ft_exit(info));
			break ;
		}
	}
}
