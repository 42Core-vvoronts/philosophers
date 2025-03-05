/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:52:43 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_thread *philo)
{
	writestatus(philo, "is sleeping");
	waittime(philo->ctx->t_sleep);
}
void	thinking(t_thread *philo)
{
	writestatus(philo, "is thinking");
}

void	eating(t_thread *philo)
{
	mxlock(&philo->leftlock, philo->ctx);
	writestatus(philo, "has taken a fork");
	mxlock(&philo->rightlock, philo->ctx);
	writestatus(philo, "has taken a fork");
	
	writestatus(philo, "is eating");
	waittime(philo->ctx->t_eat);

	mxunlock(&philo->leftlock, philo->ctx);
	mxunlock(&philo->rightlock, philo->ctx);
}

bool   everyone_alive(t_ctx *ctx)
{
	return (ctx);
}

void	*routine(void *arg)
{
	t_thread	*philo;
	t_ctx		*ctx;

	philo = (t_thread *)arg;
	ctx = philo->ctx;
	while (everyone_alive(ctx)) 
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}
