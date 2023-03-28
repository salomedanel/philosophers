/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:58:31 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/21 11:59:11 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ARG "Wrong number of arguments."
# define NDIGIT "All arguments must be digits."
# define PBINT "All arguments must fit into an absolute int and not be zero."
# define MLC "Malloc error."
# define MSF "has taken a fork"
# define MSEAT "is eating"
# define MSTH "is thinking"
# define MSSL "is sleeping"
# define MSD "died"
# define MSDONE "All meals done\n"

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef struct timeval	t_time;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long long			creation_time;
	long long			last_meal;
	int					l_fork_id;
	int					r_fork_id;
	t_info				*info;
}						t_philo;

typedef struct s_info
{
	int					nb_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_meals_todo;
	int					n_meals_done;
	int					game_over;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
}						t_info;

// utils
int						ft_atoil(char *nptr);
int						check_ifnumber(char **argv, int argc);
long long				get_time(void);
long long				get_elapsed_time(t_philo *philo);
void					ft_print(t_philo *ph, char *msg);
// init
int						check_arg(char **argv, int argc);
int						init_info(char **argv, int argc, t_info *info);
int						init_philo(t_info *info);
int						thread_init(t_info *info);
int						launch_thread(t_info *info);
// routine
void					*thread_routine(void *data);
void					philo_eat(t_philo *philo);
void					philo_sleepthink(t_philo *philo);
void					lock_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);
// check_end
int						check_endofgame(t_info *info);
int						check_death(t_info *info);
int						check_nbmeals(t_info *info);
// free
int						ft_error(char *err);
int						ft_exit(t_info *info);

#endif
