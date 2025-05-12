/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/08 19:30:19 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_thread *philo)
{
	if (philo->ctx->death)
		return ;
	writestatus(philo, "is sleeping");
	waittime(philo->ctx->t_sleep);
}
void	thinking(t_thread *philo)
{
	if (philo->ctx->death)
		return ;
	writestatus(philo, "is thinking");
}

void	eating(t_thread *philo)
{
	if (philo->ctx->death)
		return ;
	if (philo->ctx->n_ph == 1)
	{
		mxlock(philo->left, philo->ctx);
		writestatus(philo, "has taken a left fork");
		waittime(philo->ctx->t_die);
		philo->ctx->death = true;
		mxlock(philo->ctx->deadmx, philo->ctx);
		return ;
	}
	
	if (philo->id == philo->ctx->n_ph)
	{
		mxlock(philo->right, philo->ctx);
		writestatus(philo, "has taken a fork");
		mxlock(philo->left, philo->ctx);
		writestatus(philo, "has taken a fork");
	}
	else
	{	
		mxlock(philo->left, philo->ctx);
		writestatus(philo, "has taken a fork");
		mxlock(philo->right, philo->ctx);
		writestatus(philo, "has taken a fork");
	}

	
	philo->eating = true;
	writestatus(philo, "is eating");
	waittime(philo->ctx->t_eat);
	philo->ate++;
	philo->t_meal = gettime();

	mxunlock(philo->left, philo->ctx);
	mxunlock(philo->right, philo->ctx);
}

bool   everyone_alive(t_ctx *ctx)
{
	return (!ctx->death);
}

void	*routine(void *arg)
{
	t_thread	*philo;
	t_ctx		*ctx;

	philo = (t_thread *)arg;
	ctx = philo->ctx;
	sync_threads(ctx);
	while (everyone_alive(ctx)) 
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return NULL;
}
