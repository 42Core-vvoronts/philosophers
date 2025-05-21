/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:10 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 11:57:11 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	acquire_forks(t_philo *philo)
{
	if (philo->id != philo->ctx->n_philos)
	{
		mxlock(philo->right_fork, philo->ctx);
		mxlock(philo->left_fork, philo->ctx);
	}
	else
	{
		mxlock(philo->left_fork, philo->ctx);
		mxlock(philo->right_fork, philo->ctx);
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id != philo->ctx->n_philos)
	{
		mxunlock(philo->right_fork, philo->ctx);
		mxunlock(philo->left_fork, philo->ctx);
	}
	else
	{
		mxunlock(philo->left_fork, philo->ctx);
		mxunlock(philo->right_fork, philo->ctx);
	}
}

/**
 * @brief Eat routine
 * 
 * @param philo current philo
 * @param ctx context of programm
 */
void	eating(t_philo *philo, t_ctx *ctx)
{
	if (is_end(philo, ctx) || is_dead(philo))
		return ;
	acquire_forks(philo);
	if (is_end(philo, ctx) == true)
	{
		release_forks(philo);
		return ;
	}
	writestatus(philo, "has taken a fork");
	writestatus(philo, "has taken a fork");
	writestatus(philo, "is eating");
	philo->t_last_meal = philo->t_now;
	philo->n_meals++;
	if (philo->n_meals == ctx->n_meals)
		register_as_full(ctx);
	esleep(philo, ctx->t_eat);
	release_forks(philo);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}
