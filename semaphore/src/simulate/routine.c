/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:22 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	mxlock(philo->right_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	usleep(philo->ctx->t_die * 700);
	while (gettime(ctx) < ctx->t_start + philo->t_last_meal + ctx->t_die)
		usleep(10);
	mxunlock(philo->right_fork, philo->ctx);
	writedeath(philo);
	ctx->f_end = true;
	return (NULL);
}

/**
 * @brief Routine 
 * 
 * @param arg pointer to philo who runs routine
 */
void	*routine(void *arg)
{
	t_philo		*philo;
	t_ctx		*ctx;

	philo = (t_philo *)arg;
	ctx = philo->ctx;
	wait_threads(ctx);
	if (ctx->n_philos == 1)
		return (one_philo(philo, ctx));
	queue_threads(philo, ctx);
	while (true)
	{
		eating(philo, ctx);
		sleeping(philo, ctx);
		thinking(philo, ctx);
		mxlock(ctx->die_lock, ctx);
		if (ctx->f_end)
		{
			mxunlock(ctx->die_lock, ctx);
			break ;
		}
		mxunlock(ctx->die_lock, ctx);
	}
	return (NULL);
}
