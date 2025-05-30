/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 12:02:04 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	queue_threads(t_philo *philo, t_ctx *ctx)
{
	if (philo->id % 2 == 1 && philo->id == ctx->n_philos)
		esleep(philo, ctx->t_eat * 2);
	else if (philo->id % 2 == 1)
		return ;
	else
		esleep(philo, ctx->t_eat * 1);
}

void	wait_threads(t_ctx *ctx)
{
	while (true)
	{
		mxlock(ctx->uni_lock, ctx);
		if (ctx->f_ready == true)
		{
			mxunlock(ctx->uni_lock, ctx);
			break ;
		}
		mxunlock(ctx->uni_lock, ctx);
		usleep(10);
	}
	if (ctx->t_start == 0)
	{
		mxlock(ctx->uni_lock, ctx);
		if (!ctx->t_start)
			ctx->t_start = gettime(ctx);
		mxunlock(ctx->uni_lock, ctx);
	}
}

static void	create_thread(t_philo *p, void *(*f)(void *), void *arg, t_ctx *ctx)
{
	int		code;

	code = pthread_create(&p->id_pthread, NULL, f, arg);
	if (code != SUCCESS)
		ft_exit(FAIL, "pthread_create", ctx);
}

static void	join_thread(pthread_t *philo, t_ctx *ctx)
{
	int		code;

	code = pthread_join(*philo, NULL);
	if (code != SUCCESS)
		ft_exit(code, "pthread_join", ctx);
}

/**
 * @brief Creates and joins threads for each philosopher 
 * 
 * @param ctx Context of programm
 */
void	simulate(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->n_philos)
	{
		create_thread(&ctx->philos[i], routine, (void *)&ctx->philos[i], ctx);
		i++;
	}
	mxlock(ctx->uni_lock, ctx);
	ctx->f_ready = true;
	mxunlock(ctx->uni_lock, ctx);
	i = 0;
	while (i < ctx->n_philos)
	{
		join_thread(&ctx->philos[i].id_pthread, ctx);
		i++;
	}
}
