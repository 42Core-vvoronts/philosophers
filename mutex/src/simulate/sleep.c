/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 11:55:46 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sleep routine
 * 
 * @param philo current philo
 * @param ctx context of programm
 */
void	sleeping(t_philo *philo, t_ctx *ctx)
{
	if (is_end(philo, ctx) || is_dead(philo))
		return ;
	writestatus(philo, "is sleeping");
	esleep(philo, ctx->t_sleep);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}
