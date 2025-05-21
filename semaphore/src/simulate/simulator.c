/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 19:07:53 by vvoronts         ###   ########.fr       */
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

void	fork_philos(t_ctx *ctx)
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
			return ;
		}
		else if (pid == 0)
		{
			routine(ctx->philos[i], ctx);
		}
		ctx->philos[i].pid = pid;
	}
	smpost(SEMGO, ctx);
}

void	monitor_philos(t_ctx *ctx)
{
	int		i;
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == DIED)
		{
			kill_all_philos(ctx);
			break;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == FULL)
		{
			ctx->n_full++;
			if (ctx->n_meals > 0 && ctx->n_full >= ctx->n_philos)
			{
				kill_all_philos(ctx);
				break;
			}
		}
	}	
}


/**
 * @brief Creates and joins threads for each philosopher 
 * 
 * @param ctx Context of programm
 */
void    simulate(t_ctx *ctx)
{
	fork_philos(ctx);
	monitor_philos(ctx);
}
