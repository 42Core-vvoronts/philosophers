/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:26:19 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	free_forks(t_ctx *ctx)
// {
// 	int	i;

// 	i = 0;
// 	if (ctx->forks)
// 	{
// 		while (i < ctx->n_philos)
// 		{
// 			mxdestroy(&ctx->forks[i], ctx);
// 			i++;
// 		}
// 		free(ctx->forks);
// 		ctx->forks = NULL;
// 	}
// }

// void	free_lock(pthread_mutex_t *lock, t_ctx *ctx)
// {
// 	if (lock)
// 	{
// 		smdestroy(lock, ctx);
// 		free(lock);
// 		lock = NULL;
// 	}
// }

void	destroy(t_philo *philo, t_ctx *ctx)
{
	if (!ctx)
		return ;
	// free_forks(ctx);
	// free_lock(ctx->die_lock, ctx);
	// free_lock(ctx->uni_lock, ctx);
	// free_lock(ctx->write_lock, ctx);
	if (philo)
		free(philo);
	if (ctx->philos)
		free(ctx->philos);
	free(ctx);
}
