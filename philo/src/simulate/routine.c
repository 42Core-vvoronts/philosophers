/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/20 14:35:20 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo, t_ctx *ctx)
{
	if (is_end(philo, ctx) || is_dead(philo))
		return ;
	writestatus(philo, "is sleeping");
	esleep(philo, ctx->t_sleep);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}

/**
 * @brief Think routine
 * 
 * For even: eat - sleep, but if < 0 do not think
 * For odd: 2 * eat - sleep but if < 0 do not think
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

void	acquire_forks(t_philo *philo)
{
	if (philo->id != philo->ctx->n_philos)
	{
		mxlock(philo->right_fork, philo->ctx);
		mxlock(philo->left_fork, philo->ctx);
	}
	else
	{
		mxlock(philo->left_fork, philo->ctx);
		mxlock(philo->right_fork, philo->ctx);
	}
}
void	release_forks(t_philo *philo)
{
	if (philo->id != philo->ctx->n_philos)
	{
		mxunlock(philo->right_fork, philo->ctx);
		mxunlock(philo->left_fork, philo->ctx);
	}
	else
	{
		mxunlock(philo->left_fork, philo->ctx);
		mxunlock(philo->right_fork, philo->ctx);
	}
}

void	eating(t_philo *philo, t_ctx *ctx)
{
	if (is_end(philo, ctx) || is_dead(philo))
		return ;
	acquire_forks(philo);
	if (is_end(philo, ctx) == true)
	{
		release_forks(philo);
		return ;
	}
	writestatus(philo, "has taken a fork");
	writestatus(philo, "has taken a fork");
	writestatus(philo, "is eating");
	philo->t_last_meal = philo->t_now;
	philo->n_meals++;
	if (philo->n_meals == ctx->n_meals)
		register_as_full(ctx);
	esleep(philo, ctx->t_eat);
	release_forks(philo);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	mxlock(philo->right_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	usleep(philo->ctx->t_die * 700);
	while (gettime(philo->ctx) < ctx->t_start + philo->t_last_meal + philo->ctx->t_die)
		usleep(10);
	mxunlock(philo->right_fork, philo->ctx);
	// writestatus(philo, "is dead");
	writedeath(philo);
	ctx->f_end = true;
	return (NULL);
}

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
		if (ctx->f_end) {
			mxunlock(ctx->die_lock, ctx);
			break ;
		}
		mxunlock(ctx->die_lock, ctx);
	}
	return NULL;
}
