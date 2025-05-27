/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:21:27 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	smwait(ctx->forks, philo->ctx);
	writestatus(philo, "has taken a fork");
	usleep(philo->ctx->t_die * 700);
	while (gettime(ctx) < ctx->t_start + philo->t_last_meal + ctx->t_die)
		usleep(1);
	smpost(ctx->forks, philo->ctx);
	writedeath(philo);
	exit(DIED); 
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

void	check_death(t_philo *philo)
{
	if (philo->t_now <= philo->t_last_meal + philo->ctx->t_die)
		return ;
	writedeath(philo);
	ft_exit(SUCCESS, NULL, philo->ctx);
}

/**
 * @brief Routine 
 * 
 * @param arg pointer to philo who runs routine
 */
void	*routine(t_philo *philo, t_ctx *ctx)
{
	if (ctx->n_philos == 1)
		one_philo(philo, ctx);
	// sync_philos_time(ctx);
	queue_philos(philo, ctx);
	while (true)
	{
		eating(philo, ctx);
		sleeping(philo);
		thinking(philo);
		smwait(ctx->die_lock, ctx);
		if (ctx->f_end)
		{
			smpost(ctx->die_lock, ctx);
			break ;
		}
		smpost(ctx->die_lock, ctx);
	}
	return (NULL);
}
