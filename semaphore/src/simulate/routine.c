/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 19:09:34 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	smwait(ctx->forks, philo->ctx);
	writestatus(philo, "has taken a fork");
	usleep(philo->ctx->t_die * 700);
	while (gettime(ctx) < ctx->t_start + philo->t_last_meal + ctx->t_die)
		usleep(1);
	smpost(ctx->forks, philo->ctx);
	writedeath(philo);
	exit(DIED); 
}

bool	is_dead(t_philo *philo)
{
	if (philo->t_now <= philo->t_last_meal + philo->ctx->t_die)
		return (false);
	writedeath(philo);
	return (true);
}

void	queue_philos(t_philo *philo, t_ctx *ctx)
{
	if (philo->id % 2 == 1 && philo->id == ctx->n_philos)
		esleep(philo, ctx->t_eat * 2);
	else if (philo->id % 2 == 1)
		return ;
	else
		esleep(philo, ctx->t_eat * 1);
}

void	wait_philos_ready(t_ctx *ctx)
{
	smwait
	while (true)
	{
		smwait(ctx->uni_lock, ctx);
		if (ctx->f_ready == true)
		{
			smpost(ctx->uni_lock, ctx);
			break ;
		}
		smpost(ctx->uni_lock, ctx);
		usleep(1);
	}
	if (ctx->t_start == 0)
	{
		smwait(ctx->uni_lock, ctx);
		if (!ctx->t_start)
			ctx->t_start = gettime(ctx);
		smpost(ctx->uni_lock, ctx);
	}
}

/**
 * @brief Routine 
 * 
 * @param arg pointer to philo who runs routine
 */
void	*routine(t_philo *philo, t_ctx *ctx)
{
	t_ctx		*ctx;

	if (ctx->n_philos == 1)
		one_philo(philo, ctx);

	wait_philos_ready(ctx);
	queue_philos(philo, ctx);
	while (true)
	{
		eating(philo, ctx);
		sleeping(philo, ctx);
		thinking(philo, ctx);
		smwait(ctx->die_lock, ctx);
		if (ctx->f_end)
		{
			smpost(ctx->die_lock, ctx);
			break ;
		}
		smpost(ctx->die_lock, ctx);
	}
}
