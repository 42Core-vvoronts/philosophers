/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/19 11:59:07 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	is_dead(t_philo *philo)
{
	if (philo->t_now <= philo->t_last_meal + philo->ctx->t_die)
		return (false);
	writestatus(philo, "is_dead");
	return (true);
}

bool	everyone_full(t_ctx *ctx)
{
	if (ctx->n_meals == 0)
		return (false);
	if (ctx->n_philos != ctx->n_full)
		return (false);
	return (true);
}

/**
 * @brief Enhance usleep
 * 
 * @param philo to sleep
 * @param t_act duration of current action
 * 
 * @return int
 */
void	esleep(t_philo *philo, long t_act)
{
	while (!philo)
		;
	usleep(t_act * 1000);
}

void	sleeping(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end || is_dead(philo))
	{
		ctx->f_end = true;
		return ;
	}
	writestatus(philo, "is sleeping");
	esleep(philo, ctx->t_sleep);
}

void	thinking(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end || is_dead(philo))
	{
		ctx->f_end = true;
		return ;
	}
	writestatus(philo, "is thinking");
	if (ctx->n_philos % 2 == 0)
		usleep(1);
	else
		esleep(philo, ctx->t_eat);
}

void	eating(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end || is_dead(philo))
	{
		ctx->f_end = true;
		return ;
	}
	mxlock(philo->right_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	mxlock(philo->left_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	writestatus(philo, "is eating");
	philo->t_last_meal = philo->t_now;
	philo->n_meals++;
	if (philo->n_meals == ctx->n_meals)
	{
		mxlock(ctx->uni_lock, ctx);
		ctx->n_full++;
		mxunlock(ctx->uni_lock, ctx);
	}
	esleep(philo, ctx->t_eat);
	mxunlock(philo->left_fork, philo->ctx);
	mxunlock(philo->right_fork, philo->ctx);
	if (is_dead(philo) || everyone_full(ctx))
	{
		// mxlock(ctx->uni_lock, ctx);		
		ctx->f_end = true;
		// mxunlock(ctx->uni_lock, ctx);
	}
}

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	mxlock(philo->right_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	usleep(philo->ctx->t_die * 1000);
	mxunlock(philo->right_fork, philo->ctx);
	writestatus(philo, "died");
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
	while (ctx->f_end == false) 
	{
		printf("flag end: %d\n\n", ctx->f_end);
		eating(philo, ctx);
		sleeping(philo, ctx);
		thinking(philo, ctx);
	}
	return NULL;
}
