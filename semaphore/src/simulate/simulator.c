/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 15:14:21 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_thread(pthread_t *thread, void *(*f)(void *), void *arg, t_ctx *ctx)
{
	int		code;

	code = pthread_create(&thread, NULL, f, arg);
	if (code != SUCCESS)
		ft_exit(FAIL, "pthread_create", ctx);
}

static void	join_thread(pthread_t *thread, t_ctx *ctx)
{
	int		code;

	code = pthread_join(*thread, NULL);
	if (code != SUCCESS)
		ft_exit(code, "pthread_join", ctx);
}


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

bool	is_dead(t_philo *philo)
{
	if (philo->t_now <= philo->t_last_meal + philo->ctx->t_die)
		return (false);
	writedeath(philo);
	return (true);
}

void	queue_philos(t_philo *philo, t_ctx *ctx)
{
	if (philo->id % 2 == 1 && philo->id == ctx->n_philos)
		esleep(philo, ctx->t_eat * 2);
	else if (philo->id % 2 == 1)
		return ;
	else
		esleep(philo, ctx->t_eat * 1);
}

void	wait_philos_ready(t_ctx *ctx)
{
	smwait(ctx->go, ctx);
	ctx->t_delta = gettime(ctx)- ctx->t_start;
	smpost(ctx->uni_lock, ctx);
}

void	run_simulation(t_ctx *ctx)
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

void	*monitor_full(void *arg)
{
	t_ctx *ctx = (t_ctx *)arg;
	for (int i = 0; i < ctx->n_philos; i++)
		sem_wait(ctx->ful_lock);
	kill_all_philos(ctx);
	return (NULL);
}

void	monitor_death(t_ctx *ctx)
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
		
	}	
}


/**
 * @brief Creates and joins threads for each philosopher 
 * 
 * @param ctx Context of programm
 */
void    simulate(t_ctx *ctx)
{
	create_thread(ctx->observer, monitor_full, ctx, ctx);
	run_simulation(ctx);
	monitor_death(ctx);
	join_thread(ctx->observer, ctx);
}