/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:10 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 16:47:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Eat routine
 * 
 * @param philo current philo
 * @param ctx context of programm
 */
void	eating(t_philo *philo, t_ctx *ctx)
{
	check_death(philo);
	smwait(ctx->forks, ctx);
	smwait(ctx->forks, ctx);
	writestatus(philo, "has taken a fork");
	writestatus(philo, "has taken a fork");
	writestatus(philo, "is eating");
	philo->t_last_meal = philo->t_now;
	philo->n_meals++;
	if (philo->n_meals == ctx->n_meals)
		smpost(ctx->semful, ctx);
	esleep(philo, ctx->t_eat);
	smpost(ctx->forks, ctx);
	smpost(ctx->forks, ctx);
	check_death(philo);
}
