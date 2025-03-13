/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/13 11:11:11 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_threads(t_ctx *ctx)
{
	while (ctx->ready == false)
		usleep(100);
}


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
	if (philo->ctx->n_ph == 1)
	{
		philo->eating = false;
		return ;
	}

	mxlock(philo->ctx->meallock, philo->ctx);
	while (philo->ctx->philos[(philo->id - 1 + philo->ctx->n_ph) % philo->ctx->n_ph].eating ||
	philo->ctx->philos[(philo->id + 1) % philo->ctx->n_ph].eating)
	{
		mxunlock(philo->ctx->meallock, philo->ctx);
		usleep(100);
		mxlock(philo->ctx->meallock, philo->ctx);
	}
	philo->eating = true;
	mxunlock(philo->ctx->meallock, philo->ctx);

	
	mxlock(philo->left, philo->ctx);
	writestatus(philo, "has taken a left fork");
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

	alive = !ctx->death;
	return (alive);
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
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}
