/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:14:44 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 15:38:32 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	everyone_full(t_thread *philos, t_ctx *ctx)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (ctx->meals == -1)
		return (false);
	mxlock(&ctx->meallock, ctx);
	while (i < ctx->n_ph)
	{
		if (philos[i].ate == ctx->meals)
			full++;
		i++;
	}
	mxunlock(&ctx->meallock, ctx);
	if (full == ctx->n_ph)
		return (true);
	return (false);
}

bool	is_starving(t_thread philo, t_ctx *ctx)
{
	size_t	time;

	time = gettime();
	if (time - philo.t_meal > ctx->t_die)
		return (true);
	return (false);
}

bool	someone_dead(t_thread *philos, t_ctx *ctx)
{
	int	i;

	i = 0;
	mxlock(&ctx->deadlock, ctx);
	while (i < ctx->n_ph)
	{
		if (is_starving(philos[i], ctx) == true)
		{
			writestatus(&philos[i], "died");
			ctx->death = true;
			mxunlock(&ctx->deadlock, ctx);
			return (true);
		}
		i++;
	}
	mxunlock(&ctx->deadlock, ctx);
	return (false);
}

void	*monitor(void *arg)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)arg;
	while (true)
	{
		if (someone_dead(ctx->philos, ctx) == true 
			|| everyone_full(ctx->philos, ctx) == true)
			break;
	}
	return (NULL);
}
