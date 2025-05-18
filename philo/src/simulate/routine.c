/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/18 18:26:39 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end)
		return ;
	writestatus(philo, "is sleeping");
	usleep(ctx->t_sleep * 1000);
	// usleep(ctx->t_sleep * 700);
	// while (1)
	// {
	// 	if ((philo->t_last_meal + ctx->t_eat + ctx->t_sleep) <= gettime())
	// 		break ;
	// 	usleep(100);
	// }
}
void	thinking(t_philo *philo, t_ctx *ctx)
{
	long	now;
	
	if (ctx->f_end)
		return ;
	now = gettime();
	writestatus(philo, "is thinking");
	usleep(ctx->t_think * 700);
	while (ctx->t_think > gettime() - now)
		usleep(100);
}

void	eating(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end)
		return ;
	mxlock(philo->right_fork, philo->ctx);
	mxlock(philo->left_fork, philo->ctx);
	writestatus(philo, "is eating");
	philo->t_last_meal= gettime();
	philo->n_meals++;
	usleep(ctx->t_eat * 1000);
	mxunlock(philo->left_fork, philo->ctx);
	mxunlock(philo->right_fork, philo->ctx);
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
		eating(philo, ctx);
		sleeping(philo, ctx);
		thinking(philo, ctx);
	}
	return NULL;
}
