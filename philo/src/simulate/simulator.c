/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/18 17:10:00 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void queue_threads(t_philo *philo, t_ctx *ctx)
{	
	if (philo->id % 2 == 0)
		return ;
		
	if (philo->id == ctx->n_philos)
	{
		if (ctx->t_sleep > ctx->t_eat)
			usleep(ctx->t_eat * 2 * 1000);
		else
			usleep(ctx->t_sleep * 1000);
		return ;
	}
	if (ctx->t_sleep > ctx->t_eat)
		usleep(ctx->t_eat * 1000);
	else
		usleep(ctx->t_sleep * 1000);
}

void	wait_threads(t_ctx *ctx)
{
	while (ctx->f_ready == false)
		usleep(100);
	if (ctx->t_start == 0)
	{
		mxlock(ctx->uni_lock, ctx);
		if (!ctx->t_start)
			ctx->t_start = gettime();
		mxunlock(ctx->uni_lock, ctx);
	}
}

static void	create_thread(t_philo *philo, void *(*routine)(void *), void *arg, t_ctx *ctx)
{
	int		code;
	code = pthread_create(&philo->id_pthread, NULL, routine, arg);
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
	ctx->f_ready = true;
	i = 0;
	while (i < ctx->n_philos)
	{
		join_thread(&ctx->philos[i].id_pthread, ctx);
		i++;
	}
	
}
