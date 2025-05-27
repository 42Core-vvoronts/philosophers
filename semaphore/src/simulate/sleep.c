/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:21:49 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sleep routine
 * 
 * @param philo current philo
 * @param ctx context of programm
 */
void	sleeping(t_philo *philo)
{
	check_death(philo);
	writestatus(philo, "is sleeping");
	esleep(philo, philo->ctx->t_sleep);
	check_death(philo);
}
