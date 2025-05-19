/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/19 20:03:02 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	writedeath(t_philo *philo)
{
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return ;
	}
	philo->ctx->f_end = true;
	// printf("	%d died set flag true\n", philo->id);
	writestatus(philo, "is dead");
	mxunlock(philo->ctx->die_lock, philo->ctx);
}

bool	is_dead(t_philo *philo)
{	
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return (false);
	}
	mxunlock(philo->ctx->die_lock, philo->ctx);
	if (philo->t_now <= philo->t_last_meal + philo->ctx->t_die)
		return (false);
	writedeath(philo);
	return (true);
}

bool	everyone_full(t_ctx *ctx, t_philo *philo)
{
	mxlock(philo->ctx->uni_lock, philo->ctx);
	if (ctx->n_meals == 0 || ctx->n_philos != ctx->n_full)
	{
		mxunlock(philo->ctx->uni_lock, philo->ctx);
		return (false);
	}
	mxunlock(philo->ctx->uni_lock, philo->ctx);
	
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return (true);
	}
	philo->ctx->f_end = true;
	printf("\nSimulation stopped. Every one is full\n");
	mxunlock(philo->ctx->die_lock, philo->ctx);
	return (true);
}

/**
 * @brief Enhanced usleep
 * 
 * @param philo to sleep
 * @param t_act duration of current action
 * 
 * @return int
 */
void	esleep(t_philo *philo, long t_act)
{
	long	t_wake;

	philo->t_remain = philo->t_last_meal + philo->ctx->t_die - philo->t_now;
	if (philo->t_remain <= 0)
		return ;
	if (philo->t_remain >= t_act)
	{
		usleep(t_act * 700);
		t_wake = philo->ctx->t_start + philo->t_now + t_act;
		while (gettime(philo->ctx) < t_wake)
			usleep(10);
		return ;
	}
	else
	{
		usleep(philo->t_remain *700);
		t_wake = philo->ctx->t_start + philo->t_now + philo->t_remain;
		while (gettime(philo->ctx) < t_wake)
			usleep(10);
		writedeath(philo);
		// mxlock(philo->ctx->die_lock, philo->ctx);
		// philo->ctx->f_end = true;
		// // printf("	%d died set flag true\n", philo->id);
		// writestatus(philo, "is dead");
		// mxunlock(philo->ctx->die_lock, philo->ctx);
		return ;
		
	}
	
}

void	sleeping(t_philo *philo, t_ctx *ctx)
{
	if (is_dead(philo))
		return ;
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return ;
	}
	mxunlock(philo->ctx->die_lock, philo->ctx);
	writestatus(philo, "is sleeping");
	esleep(philo, ctx->t_sleep);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}

void	thinking(t_philo *philo, t_ctx *ctx)
{
	if (is_dead(philo))
		return ;
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return ;
	}
	mxunlock(philo->ctx->die_lock, philo->ctx);
	writestatus(philo, "is thinking");
	if (ctx->n_philos % 2 == 0)
		usleep(1);
	else
		esleep(philo, ctx->t_eat*2);
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}

void	eating(t_philo *philo, t_ctx *ctx)
{
	if (is_dead(philo))
		return ;
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		return ;
	}
	mxunlock(philo->ctx->die_lock, philo->ctx);
	
	if (philo->id != ctx->n_philos)
	{
		mxlock(philo->right_fork, philo->ctx);
		mxlock(philo->left_fork, philo->ctx);
	}
	else
	{
		mxlock(philo->left_fork, philo->ctx);
		mxlock(philo->right_fork, philo->ctx);
	}
	
	mxlock(philo->ctx->die_lock, philo->ctx);
	if (philo->ctx->f_end == true)
	{
		mxunlock(philo->ctx->die_lock, philo->ctx);
		if (philo->id != ctx->n_philos)
		{
			mxunlock(philo->right_fork, philo->ctx);
			mxunlock(philo->left_fork, philo->ctx);
		}
		else
		{
			mxunlock(philo->left_fork, philo->ctx);
			mxunlock(philo->right_fork, philo->ctx);
		}
		return ;
	}

	writestatus(philo, "has taken a fork");
	writestatus(philo, "has taken a fork");
	writestatus(philo, "is eating");
	
	philo->t_last_meal = philo->t_now;
	philo->n_meals++;
	if (philo->n_meals == ctx->n_meals)
	{
		mxlock(ctx->uni_lock, ctx);
		ctx->n_full++;
		mxunlock(ctx->uni_lock, ctx);
	}
	esleep(philo, ctx->t_eat);
	if (philo->id != ctx->n_philos)
	{
		mxunlock(philo->right_fork, philo->ctx);
		mxunlock(philo->left_fork, philo->ctx);
	}
	else
	{
		mxunlock(philo->left_fork, philo->ctx);
		mxunlock(philo->right_fork, philo->ctx);
	}
	if (is_dead(philo) || everyone_full(ctx, philo))
		return ;
}

void	*one_philo(t_philo *philo, t_ctx *ctx)
{
	mxlock(philo->right_fork, philo->ctx);
	writestatus(philo, "has taken a fork");
	usleep(philo->ctx->t_die * 700);
	while (gettime(philo->ctx) < ctx->t_start + philo->t_last_meal + philo->ctx->t_die)
		usleep(10);
	mxunlock(philo->right_fork, philo->ctx);
	// writestatus(philo, "is dead");
	writedeath(philo);
	ctx->f_end = true;
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_ctx		*ctx;

	philo = (t_philo *)arg;
	ctx = philo->ctx;
	wait_threads(ctx);
	if (ctx->n_philos == 1)
		return (one_philo(philo, ctx));
	queue_threads(philo, ctx);
	while (true)
	{
		eating(philo, ctx);
		sleeping(philo, ctx);
		thinking(philo, ctx);
		mxlock(ctx->die_lock, ctx);
		if (ctx->f_end) {
			mxunlock(ctx->die_lock, ctx);
			break ;
		}
		mxunlock(ctx->die_lock, ctx);
	}
	return NULL;
}
