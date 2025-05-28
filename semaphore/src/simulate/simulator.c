/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 19:49:57 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_all_philos(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->n_philos)
	{
		if (ctx->philos[i].pid != 0)
			kill(ctx->philos[i].pid, SIGKILL);
		i++;
	}
}

static void	create_philos(t_ctx *ctx)
{
	int		i;
	pid_t	pid;

	i = 0;
	ctx->t_start = gettime(ctx);
	while (i < ctx->n_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			kill_all_philos(ctx);
			destroy(ctx);
			ft_exit(FAIL, "fork");
		}
		else if (pid != 0)
			ctx->philos[i].pid = pid;
		else if (pid == 0)
			routine(&ctx->philos[i]);
		i++;
	}
	smpost(ctx->semgo, ctx);
}

/**
 * @brief Creates and joins threads for each philosopher 
 * 
 * @param ctx Context of programm
 */
void	simulate(t_ctx *ctx)
{
	create_philos(ctx);
	if (ctx->n_meals > 0 && ctx->n_philos > 1)
		create_thread(ctx->observer, &monitor_full, ctx, ctx);
	monitor_death(ctx);
	if (ctx->n_meals > 0 && ctx->n_philos > 1)
		join_thread(ctx->observer, ctx);
}
