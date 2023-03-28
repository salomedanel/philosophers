/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:32:36 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/21 11:50:50 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->info->lock);
	while (philo->info->game_over == 0)
	{
		pthread_mutex_unlock(&philo->info->lock);
		philo_eat(philo);
		philo_sleepthink(philo);
		pthread_mutex_lock(&philo->info->lock);
	}
	pthread_mutex_unlock(&philo->info->lock);
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	if (philo->info->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->info->forks[philo->l_fork_id]);
		ft_print(philo, MSF);
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork_id]);
		philo->info->game_over = 1;
		return ;
	}
	lock_forks(philo);
	ft_print(philo, MSF);
	ft_print(philo, MSF);
	ft_print(philo, MSEAT);
	pthread_mutex_lock(&philo->info->lock);
	philo->last_meal = get_elapsed_time(philo);
	if (philo->info->n_meals_todo > 0)
		philo->info->n_meals_done++;
	pthread_mutex_unlock(&philo->info->lock);
	usleep(philo->info->t_eat * 1000);
	unlock_forks(philo);
}

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->info->forks[philo->l_fork_id]);
		pthread_mutex_lock(&philo->info->forks[philo->r_fork_id]);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->info->forks[philo->r_fork_id]);
		pthread_mutex_lock(&philo->info->forks[philo->l_fork_id]);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork_id]);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork_id]);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork_id]);
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork_id]);
	}
}

void	philo_sleepthink(t_philo *philo)
{
	ft_print(philo, MSSL);
	usleep(philo->info->t_sleep * 1000);
	ft_print(philo, MSTH);
	if (philo->info->nb_philo % 2 == 1)
		usleep(philo->info->t_eat * 1000);
	else
		usleep(1000);
}
