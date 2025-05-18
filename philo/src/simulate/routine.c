/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/18 11:08:02 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end)
		return ;
	writestatus(philo, "is sleeping");
	waittime(philo->ctx->t_sleep);
}
void	thinking(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end)
		return ;
	writestatus(philo, "is thinking");
}

void	eating(t_philo *philo, t_ctx *ctx)
{
	if (ctx->f_end)
		return ;
	mxlock(philo->right_fork, philo->ctx);
	mxlock(philo->left_fork, philo->ctx);
	writestatus(philo, "is eating");
	waittime(ctx->t_eat);
	philo->t_last_meal= gettime();
	philo->n_meals++;
	mxunlock(philo->left_fork, philo->ctx);
	mxunlock(philo->right_fork, philo->ctx);
}

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	mxlock(philo->right_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	waittime(philo->ctx->t_die);
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
	sync_threads(ctx);
	if (ctx->n_philos == 1)
		return (one_philo(philo, ctx));
	while (ctx->f_end == false) 
	{
		eating(philo, ctx);
		sleeping(philo, ctx);
		thinking(philo, ctx);
	}
	return NULL;
}
