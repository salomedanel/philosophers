/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:58:00 by sdanel            #+#    #+#             */
/*   Updated: 2023/03/21 11:47:45 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (ft_error(ARG));
	if (init_info(argv, argc, &info) == 1)
		return (0);
	if (init_philo(&info) == 1)
		return (0);
	if (thread_init(&info) == 1)
		return (0);
	return (0);
}
