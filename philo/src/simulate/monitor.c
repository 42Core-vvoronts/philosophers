/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:05:13 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/20 14:06:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_end(t_philo *philo, t_ctx *ctx)
{
	mxlock(ctx->die_lock, ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(ctx->die_lock, ctx);
		return (true);
	}
	mxunlock(ctx->die_lock, ctx);
	return (false);
}
bool	is_dead(t_philo *philo)
{	
	if (philo->t_now <= philo->t_last_meal + philo->ctx->t_die)
		return (false);
	writedeath(philo);
	return (true);
}

void	register_as_full(t_ctx *ctx)
{
	mxlock(ctx->uni_lock, ctx);
	ctx->n_full++;
	mxunlock(ctx->uni_lock, ctx);
}
bool	everyone_full(t_ctx *ctx, t_philo *philo)
{
	mxlock(philo->ctx->uni_lock, philo->ctx);
	if (ctx->n_meals == 0 || ctx->n_philos != ctx->n_full)
	{
		mxunlock(philo->ctx->uni_lock, philo->ctx);
		return (false);
	}
	mxunlock(philo->ctx->uni_lock, philo->ctx);
	
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return (true);
	}
	philo->ctx->f_end = true;
	printf("\nSimulation stopped. Every one is full\n");
	mxunlock(philo->ctx->die_lock, philo->ctx);
	return (true);
}
