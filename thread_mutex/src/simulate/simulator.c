/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/12 15:24:32 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_thread(pthread_t *thread, void *(*routine)(void *), void *arg, t_ctx *ctx)
{
	int		code;
	code = pthread_create(thread, NULL, routine, arg);
	if (code != SUCCESS)
		ft_exit(FAIL, "pthread_create", ctx);
}

static void	join_thread(pthread_t thread, t_ctx *ctx)
{
	int		code;
	code = pthread_join(thread, NULL);
	if (code != SUCCESS)
		ft_exit(code, "pthread_join", ctx);	
}

static void	detach_thread(pthread_t thread, t_ctx *ctx)
{
	int		code;
	code = pthread_detach(thread);
	if (code != SUCCESS)
		ft_exit(code, "pthread_detach", ctx);
}

void	sync_threads(t_ctx *ctx)
{
	long start_time;
	while (ctx->f_ready == false)
		usleep(100);
	mxlock(ctx->write_lock, ctx);
	start_time = gettime();
	if (!ctx->t_born)
	{
		ctx->t_born = start_time;
		for (int i = 0; i < ctx->n_ph; i++)
			ctx->philos[i].t_meal = start_time;
	}
	mxunlock(ctx->write_lock, ctx);
}

/**
 * @brief Creates and joins threads for waiter and each philosopher 
 * 
 * @param ctx Context of programm
 */
void	simulate(t_ctx **ctx)
{
	t_thread	*philo;
	int			i;

	i = 0;
	create_thread(&(*ctx)->waiter, monitor, *ctx, *ctx);
	while (i < (*ctx)->n_ph)
	{
		philo = &(*ctx)->philos[i];
		init_philo(philo, *ctx, i);
		create_thread(&philo->thread, routine, philo, *ctx);
		detach_thread(philo->thread, *ctx);
		i++;
	}
	(*ctx)->f_ready = true;
	join_thread((*ctx)->waiter, *ctx);
}
