/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:05:13 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 18:54:17 by vvoronts         ###   ########.fr       */
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
		if (ctx->f_death == true)
			break ;
		i++;
	}
	if (ctx->f_death == false)
		kill_all_philos(ctx);
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
			ctx->f_death = true;
			smpost(ctx->semful, ctx);
			kill_all_philos(ctx);
			break ;
		}
	}
}
