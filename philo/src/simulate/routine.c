/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/07 18:50:47 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_thread *philo)
{
	writestatus(philo, "is sleeping");
	waittime(philo->ctx->t_sleep);
}
void	thinking(t_thread *philo)
{
	writestatus(philo, "is thinking");
}

void	eating(t_thread *philo)
{
	mxlock(philo->left, philo->ctx);
	writestatus(philo, "has taken a left fork");
	if (philo->ctx->n_ph == 1)
	{
		philo->starve = true;
		mxunlock(philo->left, philo->ctx);
		return ;
	}
	mxlock(philo->right, philo->ctx);
	writestatus(philo, "has taken a right fork");
	writestatus(philo, "is eating");
	waittime(philo->ctx->t_eat);
	philo->ate++;
	philo->t_meal = gettime();

	mxunlock(philo->left, philo->ctx);
	mxunlock(philo->right, philo->ctx);
}

bool   everyone_alive(t_ctx *ctx)
{
	bool	alive;

	mxlock(&ctx->deadlock, ctx);
	alive = !ctx->death;
	mxunlock(&ctx->deadlock, ctx);
	return (alive);
}

void	*routine(void *arg)
{
	t_thread	*philo;
	t_ctx		*ctx;

	philo = (t_thread *)arg;
	ctx = philo->ctx;
	while (everyone_alive(ctx)) 
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}
