/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:18 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 11:55:58 by vvoronts         ###   ########.fr       */
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
void	thinking(t_philo *philo, t_ctx *ctx)
{
	if (is_end(philo, ctx) || is_dead(philo))
		return ;
	writestatus(philo, "is thinking");
	if (philo->t_think == 0)
		usleep(1);
	else
		esleep(philo, philo->t_think);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}
