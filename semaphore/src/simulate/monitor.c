/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:05:13 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 19:08:00 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_full(void *arg)
{
	t_ctx	*ctx;
	int		i;

	ctx = (t_ctx *)arg;
	i = 0;
	while (i < ctx->n_philos)
	{
		smwait(ctx->semful, ctx);
		smwait(ctx->semdie, ctx);
		if (ctx->f_death == true)
		{
			smpost(ctx->semdie, ctx);
			break ;
		}
		smpost(ctx->semdie, ctx);
		i++;
	}
	smwait(ctx->semdie, ctx);
	if (ctx->f_death == false)
		kill_all_philos(ctx);
	smpost(ctx->semdie, ctx);
	return (NULL);
}

void	monitor_death(t_ctx *ctx)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == DIED)
		{
			smwait(ctx->semdie, ctx);
			ctx->f_death = true;
			smpost(ctx->semdie, ctx);
			ctx->f_death = true;
			smpost(ctx->semful, ctx);
			kill_all_philos(ctx);
			break ;
		}
	}
}
