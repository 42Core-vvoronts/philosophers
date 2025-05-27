/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:19:52 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    kill_all_philos(t_ctx *ctx)
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

// void	sync_philos_time(t_ctx *philo)
// {
// 	smwait(SEMGO, ctx);
// 	ctx->t_delta = gettime(ctx)-ctx->t_start;
// 	smpost(SEMGO, ctx);
	
// }

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
			ft_exit(FAIL, "fork", ctx);
		}
		else if (pid == 0)
			routine(&ctx->philos[i], ctx);
		ctx->philos[i].pid = pid;
	}
	// smpost(SEMGO, ctx);
}

/**
 * @brief Creates and joins threads for each philosopher 
 * 
 * @param ctx Context of programm
 */
void    simulate(t_ctx *ctx)
{
	create_thread(ctx->observer, &monitor_full, ctx, ctx);
	create_philos(ctx);
	monitor_death(ctx);
	join_thread(ctx->observer, ctx);
}
