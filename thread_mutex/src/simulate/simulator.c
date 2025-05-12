/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/12 17:20:11 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_thread(pthread_t *philo, void *(*routine)(void *), void *arg, t_ctx *ctx)
{
	int		code;
	code = pthread_create(philo, NULL, routine, arg);
	if (code != SUCCESS)
		ft_exit(FAIL, "pthread_create", ctx);
}

static void	join_thread(pthread_t *philo, t_ctx *ctx)
{
	int		code;
	code = pthread_join(philo, NULL);
	if (code != SUCCESS)
		ft_exit(code, "pthread_join", ctx);	
}

static void	detach_thread(pthread_t *philo, t_ctx *ctx)
{
	int		code;
	code = pthread_detach(philo);
	if (code != SUCCESS)
		ft_exit(code, "pthread_detach", ctx);
}

void	sync_threads(t_ctx *ctx)
{
	while (ctx->f_ready == false)
		usleep(100);
	if (!ctx->t_start)
	{
		mxlock(ctx->uni_lock, ctx);
		if (!ctx->t_start)
			ctx->t_start = gettime();
		mxunlock(ctx->uni_lock, ctx);
	}
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
		create_thread(&ctx->philos[i], routine, ctx->philos[i], ctx);
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
