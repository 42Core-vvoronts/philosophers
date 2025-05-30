/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:18 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:20:50 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Think routine
 * 
 * Time to think is counted during philo init
 * @param philo current philo
 * @param ctx context of programm
 */
void	thinking(t_philo *philo)
{
	check_death(philo);
	writestatus(philo, "is thinking");
	if (philo->t_think == 0)
		usleep(1);
	else
		esleep(philo, philo->t_think);
	check_death(philo);
}
